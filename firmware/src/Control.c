#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;

void CONTROL_Initialize ( void )
{
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void CONTROL_Tasks ( void )
{
    SetServoGripperPWM(30);
//    struct JsonResponse js;
//    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
//    if(ret == pdTRUE)
//    {
//         
//    }
}
void SendToControlQueue(struct JsonResponse js)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(receive_q, &js, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
