#include "control.h"

CONTROL_DATA controlData;
QueueHandle_t receive_q;
TimerHandle_t myTimer;
bool bumper = false;
bool iscipangoready = false;
void CONTROL_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    controlData.state = CONTROL_STATE_INIT;
    controlData.current_row = 0;
    controlData.standby = false;
    controlData.enterstandby = true;
    controlData.enterturnright = true;
    controlData.enterturnleft = true;
    controlData.entertare = true;
    controlData.enterback = true;
    controlData.entersweep = true;
    controlData.dump = true;
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    myTimer = xTimerCreate("LoriTimer", 250, pdTRUE, (void*)0, LoriTimer1CallBack);
    DRV_ADC_Open();
    DRV_ADC_Start();
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void CONTROL_Tasks ( void )
{
    while(1)
    {
    static int FrontDistance = 0;
    static int SideDistance = 0;
    struct JsonResponse js = {0, 0, 0, 0, 0};
    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 5);
    if(js.tsk == 49)
    {
        FrontDistance = js.arg0;
        SideDistance = js.arg1;
    }
    else if(js.tsk == 90)
    {
        iscipangoready = (js.arg0) ? true : false;
    }
    /* Check the application's current state. */
    switch ( controlData.state )
    {
        /* Application's initial state. */
        case CONTROL_STATE_INIT:
        {
//            bool appInitialized = true;
            bumper = false;
            controlData.state = CONTROL_STATE_SWEEP;
            if (js.tsk == 80 && js.arg0 == 1)
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
            controlData.state = CONTROL_STATE_SWEEP;            
            break;
        }

        case CONTROL_STATE_STANDBY:
        {
            if(controlData.enterstandby)
            {
                Left_Motor_Distance(FORWARD, 50, 750 * controlData.current_row);
                Right_Motor_Distance(FORWARD, 50, 750 * controlData.current_row);
                controlData.enterstandby = false;
            }
            if(Left_Is_Finish() && Right_Is_Finish())
            {
//                controlData.enterstandby = true;
                controlData.standby = true;
                controlData.state = CONTROL_STATE_TURN_RIGHT;
            }
            break;
        }
        
        case CONTROL_STATE_TURN_RIGHT:
        {
            if(controlData.enterturnright)
            {
                Left_Motor_Distance(FORWARD, 50, 540);
                Right_Motor_Distance(BACKWARD, 50, 540);                
                controlData.enterturnright = false;
            }
            if(Left_Is_Finish() && Right_Is_Finish())
            {
//                controlData.enterturn = true;
                if(controlData.standby)
                {
                    controlData.standby = false;
                    controlData.state = CONTROL_STATE_TARE;
                }
                else
                {
//                    controlData.standby = true;
                    controlData.state = CONTROL_STATE_DUMP;
                }
            }
            break;
        }
        
        case CONTROL_STATE_TARE:
        {
            if(controlData.entertare)
            {
                Left_Motor_Distance(BACKWARD, 50, 1500);
                Right_Motor_Distance(BACKWARD, 50, 1500); 
                controlData.entertare = false;
            }
            if(bumper)
            {
                bumper = false;
//                controlData.entertare = true;
                controlData.state = CONTROL_STATE_SWEEP;
            }
            break;            
        }
        
        case CONTROL_STATE_SWEEP:
        {
            if(controlData.entersweep)
            {
                Left_Motor_Distance(FORWARD, 45, 7000);
                Right_Motor_Distance(FORWARD, 45, 7000);
                controlData.entersweep = false;
            }
            if(Left_Is_Finish() && Right_Is_Finish())
            {
//                controlData.entersweep = true;
                controlData.state = CONTROL_STATE_BACK;
            }    
            break;
        }
        
        case CONTROL_STATE_BACK:
        {
            if(controlData.enterback)
            {
                Left_Motor_Distance(BACKWARD, 45, 8000);
                Right_Motor_Distance(BACKWARD, 45, 8000);
                controlData.enterback = false;
//                Left_Motor_PID(BACKWARD, 45);
//                Right_Motor_PID(BACKWARD, 45);
            }
            if(bumper)
            {
                Left_Motor_Distance(FORWARD, 45, 450);
                Right_Motor_Distance(FORWARD, 45, 450);
                vTaskDelay((TickType_t) 500);
                bumper = false;
                controlData.dump = true;
                controlData.enterturnleft = true;
                controlData.state = CONTROL_STATE_TURN_LEFT;
            }
            break;
        }
        
        case CONTROL_STATE_TURN_LEFT:
        {
            if(controlData.enterturnleft)
            {
                Left_Motor_Distance(BACKWARD, 45, 540);
                Right_Motor_Distance(FORWARD, 45, 540);                
                controlData.enterturnleft = false;
            }
            if(Left_Is_Finish() && Right_Is_Finish())
            {
//                controlData.enterturn = true;
                if(controlData.dump)
                {
                    controlData.dump = false;                    
                    controlData.state = CONTROL_STATE_PREDUMP;
                }
                else
                {
//                    controlData.dump = true;
                    controlData.state = CONTROL_STATE_STANDBY;
                }
            }
            break;
        }
        
        case CONTROL_STATE_PREDUMP:
        {
            Left_Motor_Distance(BACKWARD, 45, 4000);
            Right_Motor_Distance(BACKWARD, 45, 4000);
            if(bumper)
            {
                bumper = false;
                Left_Motor_Distance(FORWARD, 45, 350);
                Right_Motor_Distance(FORWARD, 45, 350);
                vTaskDelay((TickType_t) 500);
                controlData.enterturnright = true;
                controlData.state = CONTROL_STATE_TURN_RIGHT;
            }
            break;
        }
        
        case CONTROL_STATE_DUMP:
        {
            Left_Motor_Distance(BACKWARD, 45, 1000);
            Right_Motor_Distance(BACKWARD, 45, 1000);
            if(bumper)
            {
                Move(45, 250, FORWARD);
                iscipangoready = false;
                Left_Motor_PID(FORWARD, 0);
                Right_Motor_PID(FORWARD, 0);
                SetServo2PWM(800);
                vTaskDelay((TickType_t) 225);
                SetServo2PWM(50);
                vTaskDelay((TickType_t) 225);
                SetServo2PWM(0);
                bumper = false;
                struct JsonRequest jsr = {PIC_ID, 's', 2, 91, 0, 1, 0, 0, 0};
                SendOverWiFi(jsr);
                controlData.current_row++;
                controlData.enterback = true;
                controlData.dump = false;
                controlData.enterstandby = true;
                controlData.entersweep = true;
                controlData.entertare = true;
                controlData.enterturnright = true;
                controlData.standby = false;
                bumper = false;
                controlData.enterturnleft = true;
                controlData.state = (controlData.current_row >= 3) ? CONTROL_STATE_END : CONTROL_STATE_TURN_LEFT;  
            }            
//            Left_Motor_PID(BACKWARD, 45);
//            Right_Motor_PID(BACKWARD, 45);
//            if(!iscipangoready)
//            {
//                BaseType_t ret = xTimerStart(myTimer, (TickType_t) 5);
//                if(ret == pdFAIL)
//                {
//                    
//                }
//            }
//            else
//            {
//                BaseType_t ret = xTimerStop(myTimer, (TickType_t) 5);
//                if(ret == pdFAIL)
//                {
//                
//                }
//
//            }
            break;
        }
        
        case CONTROL_STATE_SERVICE_TASKS:
        {

        }
        default:
        {
            break;
        }
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
        
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void LoriTimer1CallBack(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', 2, 90, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}
