#include "motor_encoder_thread.h"

QueueHandle_t Encoder_Q;
int left = 0;
int right = 0;
//
void MOTOR_ENCODER_THREAD_Initialize ( void )
{
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    //DRV_OC0_Enable();
    DRV_OC0_Start();
    //DRV_OC1_Enable();
    DRV_OC1_Start();
    //init q
    Encoder_Q = xQueueCreate( 10, sizeof(Encoder) );
    if (!Encoder_Q)
    {
        //sendToUART('c');
    }
}


void MOTOR_ENCODER_THREAD_Tasks ( void )
{
    Motor_Left_Set(BACKWARD, 75);
    Motor_Right_Set(BACKWARD, 75);
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
            left = data.Encoder_Left_Speed;
            right = data.Encoder_Right_Speed;
        }
    }
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