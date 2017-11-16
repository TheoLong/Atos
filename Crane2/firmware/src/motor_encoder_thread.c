#include "motor_encoder_thread.h"
#include "public.h"

FLAG flag = {false,false};
TIME_CONTROL time_control = {0,0};
SERVO rotor = {0};
SERVO gripper = {0};
SERVO winch = {0};
SERVO wrist = {0};


void MOTOR_ENCODER_THREAD_Initialize ( void )
{
    //start timer and OC
    DRV_TMR0_Start();
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    //init Q to receive encoder
    Timing_Q = xQueueCreate( 10, sizeof(timing) );
    //if queue create failed
    if (!Timing_Q)
    {
        //sendToUART('c'); 
    }    
}


void MOTOR_ENCODER_THREAD_Tasks ( void )
{
    DRV_OC0_PulseWidthSet(rotor.pwm);
    DRV_OC3_PulseWidthSet(gripper.pwm);
    DRV_OC2_PulseWidthSet(winch.pwm);
    DRV_OC1_PulseWidthSet(wrist.pwm);
    timing data;
    BaseType_t receive;
    receive = xQueueReceive(Timing_Q, &data, portMAX_DELAY);
    //-----------------------------------not received data
    if (receive == pdFALSE)
    {
        //sendToUART('r');
    }
    //-----------------------------------received data
    else
    {
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
    }
}

void read_timing(void)
{
    timing data = {true};
    SendToQueue(data);
}


void SendToQueue(timing data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(Timing_Q, &data, &xHigherPriorityTaskWoken);
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

void SetServoRotorPWM(int pwm)
{
    rotor.pwm = pwm;
}

void SetServoGripperPWM(int pwm)
{
    gripper.pwm = pwm;
}
void SetServoWinchPWM(int pwm)
{
    winch.pwm = pwm;
}

void SetServoWristPWM(int pwm)
{
    wrist.pwm = pwm;
}