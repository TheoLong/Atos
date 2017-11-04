#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;
bool startRemoving=false;
bool init = false;
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
    if(!init)
    {
        //init==========================
        init = true;
        SetServoGripperPWM(500); // gripper 500 for open, 750 for close
        SetServoRotorPWM(130);//130 for 0, 750 for 180
        SetServoWristPWM(170);//170 for init, 800 for flip
        //move winch up
        bumperTop = false;
        while(!bumperTop)
		{
			SetServoWinchPWM(700); //700 is up, 10 is down
		}
        SetServoWinchPWM(0);//stop winch
        //trigger signal from server
    }
    
    if (!startRemoving)
    {
        startRemoving = true;
        //===========	move the arm down
        bumperBot = false;
        while(!bumperBot)
        {
            SetServoWinchPWM(10);
        }
        
        SetServoWinchPWM(0);//stop winch
        //===========	close gripper
        Wait_Time(1000);//wait 1 second
        SetServoGripperPWM(750);
        Wait_Time(1000);//wait 1 second
        //===========	move the arm up
        bumperTop = false;
        while(!bumperTop)
        {
            SetServoWinchPWM(700);
        }
        
        SetServoWinchPWM(0);//stop winch
        Wait_Time(1000);//wait 1 second
        //===========	rotate the Crane
        SetServoRotorPWM(750);
        Wait_Time(1000);//wait 1 second
        //===========	dump contents
        SetServoWristPWM(800);//vertical position
        Wait_Time(1000);//wait 1 second
        SetServoWristPWM(170);//level pisition
        Wait_Time(1000);//wait 1 second
        //===========	rotate the Crane
        SetServoRotorPWM(130);
        Wait_Time(1000);//wait 1 second
        //===========	move the arm down
        bumperBot = false;
        while(!bumperBot)
        {
            SetServoWinchPWM(10); //assume 0 as moving down, otherwise change to 100
        }
        
        SetServoWinchPWM(0);//stop winch
        //===========	open gripper
        Wait_Time(1000);//wait 1 second
        SetServoGripperPWM(500);//assume 0 is close, otherwise change to 80
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
