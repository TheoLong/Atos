#include "control.h"

QueueHandle_t receive_q;


void CONTROL_Initialize ( void )
{
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    DRV_ADC_Open();
    DRV_ADC_Start();
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void CONTROL_Tasks ( void )
{
 
}


void ReadIR(void)
{
    int FrontIR = 0;
    int SideIR = 0;
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR =  DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);
        struct JsonResponse js = {49, 0, FrontIR, SideIR, 0, 0};
        SendToIRQueue(js);        
    }

}

void SendToIRQueue(struct JsonResponse js)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(receive_q, &js, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
