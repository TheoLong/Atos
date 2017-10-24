#include "control.h"

CONTROL_DATA controlData;
QueueHandle_t receive_q;


void CONTROL_Initialize ( void )
{
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
            if(bumper >= 1)
            {
//                Left_Turn();
//                Timing_Wait(500);
//                while(!GetTimingFlag())
//                {
//                }
//                Right_Turn();
//                Timing_Wait(500);
//                while(!GetTimingFlag())
//                {
//                }
                //Move(45, 7000, FORWARD);
                Left_Motor_PID(BACKWARD, 36);
                Right_Motor_PID(BACKWARD, 35);
//                Timing_Wait(20000);
//                while(!GetTimingFlag())
//                {
//                }
//                Left_Motor_PID(FORWARD, 0);
//                Right_Motor_PID(FORWARD, 0);
//                SetServo2PWM(770);
//                Wait_Time(800);
//                SetServo2PWM(0);
//                Wait_Time(800);
//                SetServo2PWM(50);
//                Wait_Time(800);
//                SetServo2PWM(0);
//                Wait_Time(800);
                controlData.state = CONTROL_STATE_SERVICE_TASKS;
                break;
            }
            
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
            //Wait_Time(800);
//            struct JsonRequest js = {PIC_ID, 's',31, 0, 1, 0, 0, 0};
//            SendOverWiFi(js);
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
