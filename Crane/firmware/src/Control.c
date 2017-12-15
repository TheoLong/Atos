#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;

TimerHandle_t controltimer;

static bool startRemoving=false;
static bool init = false;
void CONTROL_Initialize ( void )
{
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    
    controltimer = xTimerCreate("ControlTimer", 200, pdTRUE, (void*)0, requeststatus);
    
    BaseType_t ret = xTimerStart(controltimer, (TickType_t) 5);
    
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void CONTROL_Tasks ( void )
{
    if(!init)
    {
        struct JsonRequest status_js = {PIC_ID, 's', 0, 83, 0, 1, 0, 0, 0};
        SendOverWiFi(status_js);
        
        //init==========================
        init=true;
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
        struct JsonRequest jss = {0, 's', 0, 79, 0, -1, -1, 0, -1};
        SendOverWiFi(jss);
        
        struct JsonRequest status_js_done = {PIC_ID, 's', 0, 83, 0, 2, 0, 0, 0};
        SendOverWiFi(status_js_done);
    }
    
    struct JsonResponse js;
    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
    if(ret == pdTRUE)
    {
        if(js.tsk == 79 && js.arg2 == 1 && js.arg3 == 7 && init && !startRemoving)
        {
            startRemoving = true;
            struct JsonRequest jss = {0, 's', 0, 79, 0, -1, -1, 2, -1};
            SendOverWiFi(jss);
            struct JsonRequest status_js = {PIC_ID, 's', 0, 83, 0, 3, 0, 0, 0};
            SendOverWiFi(status_js);
        }
    }
    
    if (startRemoving && init)
    {
        startRemoving = false;
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
        SetServoWristPWM(600);//vertical position
        Wait_Time(1000);//wait 1 second
        SetServoWristPWM(170);//level position
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
        Wait_Time(1000);//wait 1 second
        init=false;
        
        struct JsonRequest jss = {3, 's', 3, 80, 0, 1, 1, 1, 1};
        SendOverWiFi(jss);
        
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

void requeststatus(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', 0, 79, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}
