#include "ir_pid.h"

int count=0;
int distance=0;
int set_distance=0;
float integral=0;
float derivative=0;
int previous_error;
float Kp =0;
float Ki=0;
float Kd=0;
int speed = 35;
bool dir = FORWARD;
bool enable = false;
QueueHandle_t receive_q;

void IR_PID_Initialize ( void )
{
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void IR_PID_Tasks ( void )
{
    struct JsonResponse js = {0, 0, 0, 0, 0};
    BaseType_t ret = xQueueReceive(receive_q, &js, portMAX_DELAY);
    if(ret == pdTRUE)
    {
        if(js.tsk == 49)
        {
            count++;
            if(count == 10)
            {
                //side IR distance
                distance = js.arg1;
                //---------------------------------
                //--------------------pid control started---------------------
                if(enable)
                {
                    int error = set_distance -distance;
                    //  error = setpoint - measured_value
                    integral = integral + error*10;
                    //  integral = integral + error*dt
                    derivative = (error - previous_error)/10.0;
                    //  derivative = (error - previous_error)/dt
                    float output = Kp*error+ Ki* integral+ Kd*derivative+0.5;
                    //  output = Kp*error + Ki*integral + Kd*derivative
                    previous_error = error;
                    //  previous_error = error  
                    Left_Motor_PID(dir, speed+output);
                    Right_Motor_PID(dir, speed);
                }
                
                count = 0;
            }
        }
    }
    
}

 