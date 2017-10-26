#include "ir_pid.h"
int FrontIR = 0;
int SideIR = 0;
int ircount=0;
int distance=0;
int set_distance=0;
float integral=0;
float derivative=0;
int previous_error;
float Kp =0.2;
float Ki=0;
float Kd=0;
int set_speed = 0;
bool set_dir = FORWARD;
bool enable = false;
float output=0;
int o =0;
QueueHandle_t ir_q;
IR ir_distance = {0, 0};

void IR_PID_Initialize ( void )
{
    DRV_ADC_Open();
    DRV_ADC_Start();
    ir_q = xQueueCreate(128, sizeof(IR));
    if(!ir_q)
    {
        //DBG: TODO;
    }
}

void IR_PID_Tasks ( void )
{
    
    BaseType_t ret = xQueueReceive(ir_q, &ir_distance, (TickType_t) 5);
    if(ret == pdFALSE)
    {
        
    }
    else
    {
        //side IR distance
        distance = ir_distance.Side_IR;
        
        struct JsonRequest js = {PIC_ID, 's',0, 32,0, distance, 0, 0, 0};
        SendOverWiFi(js);
        //--------------------pid control started---------------------
        if(enable)
        {   
            int error = set_distance -distance;
            //  error = setpoint - measured_value
            integral = integral + error*10;
            //  integral = integral + error*dt
            derivative = (error - previous_error)/10.0;
            //  derivative = (error - previous_error)/dt
            output = Kp*error+ Ki* integral+ Kd*derivative;
            //  output = Kp*error + Ki*integral + Kd*derivative
            previous_error = error;
            //  previous_error = error  
            if(output>=1)
            {
                o = 1;
            }
            else if(output <= -1)
            {
                o = -1;
            }
            else
            {
                o = output+0.5;
            }
            if(o<=0)
            {
                Left_Motor_PID(set_dir, set_speed-o);
                Right_Motor_PID(set_dir, set_speed+o);
            }
            if(o>0)
            {
                Left_Motor_PID(set_dir, set_speed-o);
                Right_Motor_PID(set_dir, set_speed+o);
            }
        }
        else
        {
            Motor_Left_Set(FORWARD, 0);
            Motor_Right_Set(FORWARD, 0);
        }
    }
}

 void ReadIR(void)
{
    
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR =  DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);      
    }
    if(ircount == 25)
    {
        IR data = {FrontIR, SideIR};
        SendToIRQueue(data);
        ircount =0;
    }
    ircount++;
}

void SendToIRQueue(IR data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(ir_q, &data, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void SetIRPID(bool dir, int speed, int distance)
{
    set_distance = distance;
    enable = true;
    set_speed = speed;
    set_dir = dir;
    integral=0;
    derivative=0;
    previous_error=0;
    
    
}

void StopIRPID(void)
{
    enable = false;
    
}
int GetFrontIR()
{
    return FrontIR;
}
int GetSideIR()
{
    return SideIR;
}
