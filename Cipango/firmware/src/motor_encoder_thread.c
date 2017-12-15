#include "motor_encoder_thread.h"
#include "public.h"

//public used for PID and PID API
PID pid_left = {0,0,0,0.6,0.01,1,0,FORWARD,0};
PID pid_right = {0,0,0,0.6,0.01,1,0,FORWARD,0};

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
        struct JsonRequest js_left = {PIC_ID, 's',0, 31,0, left, right, pid_left.speed, pid_right.speed};
        //SendOverWiFi(js_left);
        
        //----------------------------left PID mode

            int left_motor_pwm =  Left_PID_module(left, pid_left.speed, &pid_left.pwm);
            Motor_Left_Set(pid_left.dir, left_motor_pwm);
            
        //---------------------------right distance mode

            int right_motor_pwm = Right_PID_module(right,pid_right.speed, &pid_right.pwm);
            Motor_Right_Set(pid_right.dir, right_motor_pwm);
    }
}

void Forward(int speed)
{
    Left_Motor_PID(FORWARD, speed);
    Right_Motor_PID(FORWARD, speed);
}

void Backward(int speed)
{
    Left_Motor_PID(BACKWARD, speed);
    Right_Motor_PID(BACKWARD, speed);
}

void Pause()
{
    Left_Motor_PID(FORWARD, 0);
    Right_Motor_PID(FORWARD, 0);
}

//max 55 API for PID control
void Left_Motor_PID(bool dir, int speed)
{
    //set PID parameter
    pid_left.speed = speed;
    pid_left.dir = dir;
    
    //zero PID
    pid_left.integral = 0;
    pid_left.previous_error = 0;
    pid_left.derivative = 0;
}

void Right_Motor_PID(bool dir, int speed)
{
    //set PID parameter
    pid_right.speed = speed;
    pid_right.dir = dir;
    
    //zero PID
    pid_right.integral = 0;
    pid_right.previous_error = 0;
    pid_right.derivative = 0;
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


