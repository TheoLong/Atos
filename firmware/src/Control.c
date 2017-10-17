#include "control.h"

CONTROL_DATA controlData;
QueueHandle_t receive_q;


void CONTROL_Initialize ( void )
{
    ccccc = 0;
    /* Place the App state machine in its initial state. */
    controlData.state = CONTROL_STATE_INIT;
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
    struct JsonResponse js = {0, 0, 0, 0, 0};
    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 5);
    /* Check the application's current state. */
    switch ( controlData.state )
    {
        /* Application's initial state. */
        case CONTROL_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                controlData.state = CONTROL_STATE_RUN_TESTS;
            }
            break;
        }
        
        case CONTROL_STATE_RUN_TESTS:
        {
//            Left_Turn();
//            Right_Turn();
//            Move(45, 1500, FORWARD);
//            Timing_Wait(800);
//            while(!GetTimingFlag())
//            {
//            }
//            SetServo2PWM(770);
//            Wait_Time(800);
//            SetServo2PWM(0);
//            Wait_Time(800);
//            SetServo2PWM(50);
//            Wait_Time(800);
//            SetServo2PWM(0);
//            Wait_Time(800);    
            controlData.state = CONTROL_STATE_SERVICE_TASKS;            
            break;
        }

        case CONTROL_STATE_SERVICE_TASKS:
        {
            volatile int df;
            volatile int ds;
            if(ret != pdTRUE)
            {
                //TODO: dbgHLT
            }
            if(js.tsk == 49)
            {
                df = js.arg0;
                ds = js.arg1;
            }
            if(js.tsk == 50)
            {

            }        
            break;
        }
        default:
        {
            break;
        }
    }
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
