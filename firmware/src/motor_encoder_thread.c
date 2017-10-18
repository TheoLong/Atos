#include "motor_encoder_thread.h"
#include "public.h"

//public used for PID and PID API
PID pid_left = {0,0,0,0.6,0.03,0,0,FORWARD,0};
PID pid_right = {0,0,0,0.6,0.03,0,FORWARD,0};
DISTANCE_CONTROL left_distance_control = {0,0,0};
DISTANCE_CONTROL right_distance_control = {0,0,0};
FLAG flag = {false,false,false,false,false};
TIME_CONTROL time_control = {0,0};
SERVO servo1 = {0};
SERVO servo2 = {0};
void MOTOR_ENCODER_THREAD_Initialize ( void )
{
    //start timer and OC
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    //init Q to receive encoder
    Encoder_Q = xQueueCreate( 10, sizeof(Encoder) );
    //if queue create failed
    if (!Encoder_Q)
    {
        //sendToUART('c'); 
    }    
}


void MOTOR_ENCODER_THREAD_Tasks ( void )
{
    DRV_OC2_PulseWidthSet(servo1.pwm);
    DRV_OC3_PulseWidthSet(servo2.pwm);
    //---------------------------------counter for servo and delay-------------------------------------------------
    if(flag.counter_start)
    {
        time_control.counter = time_control.counter+100;;
    }
    if(time_control.counter >= time_control.set_time)
    {
        flag.time_up = true;
        flag.counter_start = false;
    }
    //----------------------------------read encoder data----------------------------------------------------------
    Encoder data;
    BaseType_t receive;
    //Encoder_Struct data;
    receive = xQueueReceive(Encoder_Q, &data, portMAX_DELAY);
    //-----------------------------------not received data
    if (receive == pdFALSE)
    {
        //sendToUART('r');
    }
    //-----------------------------------received data
    else
    {
        int left = data.Encoder_Left_Speed;
        int right = data.Encoder_Right_Speed;
        //---------------------------plot current speed
        struct JsonRequest js = {PIC_ID, 's',0, 31,0, left, 0, 0, 0};
        SendOverWiFi(js);
        //---------------------------using distance control or not
        if(flag.distance_mode)
        {
            left_distance_control.current_distance = left_distance_control.current_distance + left;
            right_distance_control.current_distance = right_distance_control.current_distance + right;
        }
        //----------------------------left distance control
        if(left_distance_control.current_distance > (left_distance_control.old_distance+left_distance_control.move_distance))
        {
            Motor_Left_Set(pid_left.dir, 0);
            flag.left_finish = true;
        }
        //----------------------------left PID mode
        else
        {
            int left_motor_pwm =  Left_PID_module(left,pid_left.speed, &pid_left.pwm);
            Motor_Left_Set(pid_left.dir, left_motor_pwm);
        }
        //---------------------------right distance mode
        if(right_distance_control.current_distance > (right_distance_control.old_distance+ right_distance_control.move_distance))
        {
            Motor_Right_Set(pid_right.dir, 0);
            flag.right_finish = true;
        }
        //--------------------------right PID mode
        else
        {
            int right_motor_pwm = Right_PID_module(right,pid_right.speed, &pid_right.pwm);
            Motor_Right_Set(pid_right.dir, right_motor_pwm);
        }
    }
}
//max 55 API for PID control
void Left_Motor_PID(bool dir, int speed)
{
    //set PID parameter
    pid_left.speed = speed;
    pid_left.dir = dir;
    left_distance_control.old_distance = 0;
    left_distance_control.current_distance = 0;
    left_distance_control.move_distance = 0;
    flag.distance_mode = false;
    //zero PID
    pid_left.integral = 0;
    pid_left.previous_error =0;
    pid_left.derivative =0;
}

void Right_Motor_PID(bool dir, int speed)
{
    //set PID parameter
    pid_right.speed = speed;
    pid_right.dir = dir;
    right_distance_control.old_distance = 0;
    right_distance_control.current_distance = 0;
    right_distance_control.move_distance = 0;
    flag.distance_mode = false;
    //zero PID
    pid_right.integral = 0;
    pid_right.previous_error = 0;
    pid_right.derivative = 0;
}
//PID distance function
void Left_Motor_Distance(bool dir, int speed, int distance)
{
    //set PID parameter
    pid_left.speed = speed;
    pid_left.dir = dir;
    left_distance_control.old_distance = 0;
    left_distance_control.current_distance = 0;
    left_distance_control.move_distance = distance;
    flag.distance_mode = true;
    flag.left_finish = false;
    //zero PID
    pid_left.integral = 0;
    pid_left.previous_error =0;
    pid_left.derivative =0;
}

void Right_Motor_Distance(bool dir, int speed, int distance)
{
    pid_right.speed = speed;
    pid_right.dir = dir;
    right_distance_control.old_distance = 0;
    right_distance_control.current_distance = 0;
    right_distance_control.move_distance = distance;
    flag.distance_mode = true;
    flag.right_finish = false;
    //zero PID
    pid_right.integral = 0;
    pid_right.previous_error = 0;
    pid_right.derivative = 0;
}

//Set flag for blocking API
bool Left_Is_Finish()
{
    return flag.left_finish;
}
bool Right_Is_Finish()
{
    return flag.right_finish;
}

//PID control
int Left_PID_module(int Speed, int set_speed, int*pwm)
{
    //PID control
    int error = set_speed -Speed;
    //  error = setpoint - measured_value
    pid_left.integral = pid_left.integral + error*10;
    //  integral = integral + error*dt
    pid_left.derivative = (error - pid_left.previous_error)/10.0;
    //  derivative = (error - previous_error)/dt
    float output = pid_left.Kp*error+ pid_left.Ki* pid_left.integral+ pid_left.Kd* pid_left.derivative;
    //  output = Kp*error + Ki*integral + Kd*derivative
     pid_left.previous_error = error;
    //  previous_error = error  
  
    double outpwm = *pwm+output+0.5;
    if(outpwm <0)
    {
        outpwm =0;
     }
     if(outpwm >100)
    {
        outpwm = 100;
     }
     *pwm = outpwm+0.5;
     return outpwm+0.5;
}

int Right_PID_module(int Speed, int set_speed, int*pwm)
{
    //PID control
    int error = set_speed -Speed;
    //  error = setpoint - measured_value
    pid_right.integral = pid_right.integral + error*10;
    //  integral = integral + error*dt
    pid_right.derivative = (error - pid_right.previous_error)/10.0;
    //  derivative = (error - previous_error)/dt
    float output = pid_right.Kp*error+ pid_right.Ki*pid_right.integral+ pid_right.Kd*pid_right.derivative;
    //  output = Kp*error + Ki*integral + Kd*derivative
    pid_right.previous_error = error;
    //  previous_error = error  
  
    double outpwm = *pwm+output+0.5;
    if(outpwm <0)
    {
        outpwm =0;
     }
     if(outpwm >100)
    {
        outpwm = 100;
     }
     *pwm = outpwm+0.5;
     return outpwm+0.5;
}

void Motor_Left_Set(bool dir, int pwm)
{
    //direction pin set
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, 1, dir);
    //set pwm
    DRV_OC1_PulseWidthSet(pwm);
}
void Motor_Right_Set(bool dir, int pwm)
{
    //direction pin set
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, 14, dir);
    //set pwm
    DRV_OC0_PulseWidthSet(pwm);
}

void Read_Encoders(void)
{
    uint32_t Left_Encoder_data = 1;
    uint32_t Right_Encoder_data = 1;
    Encoder data;
    Left_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_5);
    Right_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_4);
    PLIB_TMR_Counter16BitClear(TMR_ID_5);
    PLIB_TMR_Counter16BitClear(TMR_ID_4);
    data.Encoder_Left_Speed = Left_Encoder_data;
    data.Encoder_Right_Speed = Right_Encoder_data;
    SendToQueue(data);
}


void SendToQueue(Encoder data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(Encoder_Q, &data, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void Timing_Wait(int time)
{
    time_control.counter = 0;
    flag.counter_start = true;
    flag.time_up = false;
    time_control.set_time = time;
}

bool GetTimingFlag()
{
    return flag.time_up; 
}

void SetServo1PWM(int pwm)
{
    servo1.pwm = pwm;
}

void SetServo2PWM(int pwm)
{
    servo2.pwm = pwm;
}