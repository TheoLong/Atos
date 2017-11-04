#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;
bool startRemoving=false;
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
    while(1)
    {
        //init==========================
        SetServoGripperPWM(80);//initial angle for the Crane
        SetServoRotorPWM(10);//initial angle for the Crane
        SetServoWristPWM(10);//level possition
        //move winch up
        while(!bumperTop)
		{
			SetServoWinchPWM(100);//assume 100 is moving up, otherwise change to 0
		}
        bumperTop = false;
        //init==========================
        SetServoWinchPWM(0);//stop winch
        //trigger signal from server
        if (startRemoving)
        {
            //===========	move the arm down
            while(!bumperBot)
            {
                SetServoWristPWM(10); //assume 0 as moving down, otherwise change to 100
            }
            SetServoWristPWM(0);//stop winch
            //===========	close gripper
            Wait_Time(1000);//wait 1 second
            SetServoGripperPWM(10);//assume 0 is close, otherwise change to 80
            Wait_Time(1000);//wait 1 second
            //===========	move the arm up
            while(!bumperTop)
            {
                SetServoWinchPWM(100);//assume 100 is moving up, otherwise change to 0
            }
            SetServoWinchPWM(0);//stop winch
            Wait_Time(1000);//wait 1 second
            //===========	rotate the Crane
            SetServoRotorPWM(100);//assume 100 is 180 degree for the servo
            Wait_Time(1000);//wait 1 second
            //===========	dump contents
            SetServoWristPWM(50);//vertical position
            Wait_Time(1000);//wait 1 second
            SetServoWristPWM(10);//level pisition
            Wait_Time(1000);//wait 1 second
            //===========	rotate the Crane
            SetServoRotorPWM(0);//assume 100 is 180 degree for the servo
            Wait_Time(1000);//wait 1 second
            //===========	move the arm down
            while(!bumperBot)
            {
                SetServoWinchPWM(10); //assume 0 as moving down, otherwise change to 100
            }
            SetServoWinchPWM(50);//stop winch
            //===========	open gripper
            Wait_Time(1000);//wait 1 second
            SetServoGripperPWM(80);//assume 0 is close, otherwise change to 80
        }
    }
}
//    struct JsonResponse js;
//    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
//    if(ret == pdTRUE)
//    {
//         
//    }

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
