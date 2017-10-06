#include "motor_encoder_thread.h"
#include "public.h"
//Public used for debug
int left = 0;
int right = 0;
uint32_t Left_Encoder_data = 1;
uint32_t Right_Encoder_data = 1;

//public used for PID and PID API
int integral = 0;
int previous_error =0;
double derivative =0;
int speed_left = 0;
int speed_right = 0;
bool dir_left = FORWARD;
bool dir_right = FORWARD;
double Kp = 0.8;
double Ki = 0;
double Kd = 0;
int leftpwm = 0;
int rightpwm = 0;
//distance control
int left_old_distance = 0;
int left_current_distance =0;
int left_move_distance = 0;
int right_old_distance = 0;
int right_current_distance =0;
int right_move_distance = 0;
bool distance_mode = false;
//
bool left_finish = false;
bool right_finish = false;
void MOTOR_ENCODER_THREAD_Initialize ( void )
{
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    DRV_OC0_Start();
    DRV_OC1_Start();
    //init Q to receive encoder
    Encoder_Q = xQueueCreate( 10, sizeof(Encoder) );
    if (!Encoder_Q)
    {
        //sendToUART('c'); 
    }
}


void MOTOR_ENCODER_THREAD_Tasks ( void )
{
    while(1)
    {
        Encoder data;
        BaseType_t receive;
        //Encoder_Struct data;
        receive = xQueueReceive(Encoder_Q, &data, portMAX_DELAY);
        //received data
        if (receive == pdFALSE)
        {
            //sendToUART('r');
        }
        else
        {
            //perform PID with encoder data
            left = data.Encoder_Left_Speed;
            right = data.Encoder_Right_Speed;
            if(distance_mode)
            {
                left_current_distance = left_current_distance + left;
                right_current_distance = right_current_distance + right;
            }
            if(left_current_distance > (left_old_distance+left_move_distance))
            {
                Motor_Left_Set(dir_left, 0);
                left_finish = true;
            }
            else
            {
                int left_motor_pwm =  PID_module(left,speed_left, &leftpwm);
                Motor_Left_Set(dir_left, left_motor_pwm);
            }
            if(right_current_distance > (right_old_distance+right_move_distance))
            {
                Motor_Right_Set(dir_right, 0);
                right_finish = true;
            }
            else
            {
                int right_motor_pwm = PID_module(right,speed_right, &rightpwm);
                Motor_Right_Set(dir_right, right_motor_pwm);
            }
        }
    }
}
//max 55 API for PID control
void Left_Motor_PID(bool dir, int speed)
{
    speed_left = speed;
    dir_left = dir;
    left_old_distance = 0;
    left_current_distance = 0;
    left_move_distance = 0;
    distance_mode = false;
}

void Right_Motor_PID(bool dir, int speed)
{
    speed_right = speed;
    dir_right = dir;
    right_old_distance = 0;
    left_current_distance = 0;
    right_move_distance = 0;
    distance_mode = false;
}
//PID distance function
void Left_Motor_Distance(bool dir, int speed, int distance)
{
    speed_left = speed;
    dir_left = dir;
    left_old_distance = 0;
    left_current_distance = 0;
    left_move_distance = distance;
    distance_mode = true;
    left_finish = false;
}

void Right_Motor_Distance(bool dir, int speed, int distance)
{
    speed_right = speed;
    dir_right = dir;
    right_old_distance = 0;
    right_current_distance = 0;
    right_move_distance = distance;
    distance_mode = true;
    right_finish = false;
}

bool Left_Is_Finish()
{
    return left_finish;
}
bool Right_Is_Finish()
{
    return right_finish;
}


int PID_module(int Speed, int set_speed, int*pwm)
{
    //PID control
    int error = set_speed -Speed;
    //  error = setpoint - measured_value
    integral = integral + error*10;
    //  integral = integral + error*dt
    derivative = (error - previous_error)/10.0;
    //  derivative = (error - previous_error)/dt
    int output = Kp*error+Ki*integral+Kd*derivative;
    //  output = Kp*error + Ki*integral + Kd*derivative
    previous_error = error;
    //  previous_error = error  
    int outpwm = *pwm+output;
    if(outpwm <0)
    {
        outpwm =0;
     }
     if(outpwm >100)
    {
        outpwm = 100;
     }
     *pwm = outpwm;
     return outpwm;
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
    
    Encoder data;
    Left_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_3);
    Right_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_4);
    PLIB_TMR_Counter16BitClear(TMR_ID_3);
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