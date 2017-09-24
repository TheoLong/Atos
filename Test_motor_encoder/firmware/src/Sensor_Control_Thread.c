#include "sensor_control_thread.h"

QueueHandle_t IR_Q;
void SENSOR_CONTROL_THREAD_Initialize ( void )
{
    DRV_ADC_Open();
    IR_Q = xQueueCreate( 10, sizeof(IR) );
    if (!IR_Q)
    {
        //sendToUART('c');
    }
}

void SENSOR_CONTROL_THREAD_Tasks ( void )
{
    while(1)
    {
    }
}

void ReadIR(void)
{
    int FrontIR = 0;
    int SideIR = 0;
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR = DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);
    }
    IR data;
    data.Front_IR = FrontIR;
    data.Side_IR = SideIR;
    SendToIRQueue(data);
    
}

void SendToIRQueue(IR data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(IR_Q, &data, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}