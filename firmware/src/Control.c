#include "control.h"

CONTROL_DATA controlData;
QueueHandle_t receive_q;


void CONTROL_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    controlData.state = CONTROL_STATE_INIT;
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
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
               //PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 1);
               //Left_Motor_PID(FORWARD,35); 
               //Right_Motor_PID(FORWARD,35);
               SetIRPID(BACKWARD, 35);
//               while(GetFrontIR() < 700)
//               {
//                }
               //Left_Motor_PID(FORWARD,35);
               //Right_Motor_PID(FORWARD,35);
//               StopIRPID(); 
//               Left_Motor_PID(FORWARD,0);
//                Right_Motor_PID(FORWARD,0);
//               //-----------wait some time
//               SetServo1PWM(760);
//               Timing_Wait(1000);
//               while(!GetTimingFlag())
//               {
//               }
//               PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 0);
//               Move(35, 1000, FORWARD);        
//               SetIRPID(BACKWARD, 30, GetSideIR());
//               bumper =0;
               controlData.state = CONTROL_STATE_SERVICE_TASKS;
               break;
            }
            
        }
        
        case CONTROL_STATE_SERVICE_TASKS:
        {
//            if(bumper >= 1)
//            {
//               StopIRPID(); 
//               Left_Motor_PID(FORWARD,0);
//                Right_Motor_PID(FORWARD,0);
//               SetServo1PWM(50);
//               Timing_Wait(1000);
//               while(!GetTimingFlag())
//               {
//               }
//               SetServo2PWM(770);
//               Wait_Time(1500);
//               while(!GetTimingFlag())
//               {
//               }
//               SetServo2PWM(0);
//               controlData.state = CONTROL_STATE_END;
//               break;
//            }
        }
        default:
        {
            break;
        }
    }
}



