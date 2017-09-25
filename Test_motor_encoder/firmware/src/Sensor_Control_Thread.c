#include "sensor_control_thread.h"


int df =2 ;
int ds = 2;
int FrontIR = 0;
int SideIR = 0;

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
        IR data;
        BaseType_t receive;
        //IR data;
        receive = xQueueReceive(IR_Q, &data, portMAX_DELAY);
        //received data
        if (receive == pdFALSE)
        {
            //sendToUART('r');
        }
        else
        {
            df = data.Front_IR;
            ds = data.Side_IR;
        }
    }
}

void ReadIR(void)
{
    
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR = DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);
    }
    IR data;
    data.Front_IR = FrontIR;
    data.Side_IR = SideIR;
    SendToIRQueue(data);
    //
    struct JsonRequest test = {PIC_ID,'s',0,31,0,15,0,0,0};
    SendOverWiFi(test);
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