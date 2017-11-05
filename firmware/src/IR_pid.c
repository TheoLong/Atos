#include "ir_pid.h"

IRPID irpid = {0,0,0,0.1,0,0,0,FORWARD,false,0,0,0};
IRC ir= {0,0,0,0};
bool unset = false;
QueueHandle_t ir_q;
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
    IR ir_distance = {0, 0};
    BaseType_t ret = xQueueReceive(ir_q, &ir_distance, (TickType_t) 5);
    if(ret == pdFALSE)
    {
        
    }
    else
    {
        //side IR distance
        ir.distance = ir_distance.Side_IR;
        
        //--------------------pid control started---------------------
        if(irpid.enable)
        {   
            int error = irpid.set_distance -ir.distance;
            //  error = setpoint - measured_value
            irpid.integral = irpid.integral + error*10;
            //  integral = integral + error*dt
            irpid.derivative = (error - irpid.previous_error)/10.0;
            //  derivative = (error - previous_error)/dt
            irpid.output = irpid.Kp*error+ irpid.Ki* irpid.integral+ irpid.Kd*irpid.derivative;
            //  output = Kp*error + Ki*integral + Kd*derivative
            irpid.previous_error = error;
            //  previous_error = error  
           
            if(irpid.set_dir == FORWARD)
            {
                int round =0;
                if(irpid.output>=2)
                {
                    round = 2;
                }
                else if(irpid.output <= -2)
                {
                    round = -2;
                }
                else
                {
                    round = 0;
                }
                Left_Motor_PID(FORWARD, irpid.set_speed);
                Right_Motor_PID(FORWARD, irpid.set_speed);
            }
            else
            {
                int round = 0;
                if(irpid.output>=2)
                {
                    irpid.cap = 2;
                }
                else if(irpid.output <= -2)
                {
                    irpid.cap = -2;
                }
                else
                {
                    round = 0;
                }
                Left_Motor_PID(irpid.set_dir, irpid.set_speed+2);
                Right_Motor_PID(irpid.set_dir, irpid.set_speed);
            }
            struct JsonRequest js = {PIC_ID, 's',0, 32,0, ir.distance, irpid.cap, 0, 0};
            SendOverWiFi(js);
        }
        else
        {
            if(unset == false)
            {
                Left_Motor_PID(FORWARD,0);
                Right_Motor_PID(FORWARD,0);
                unset = true;
            }
        }
    }
}

 void ReadIR(void)
{
    
    if (DRV_ADC_SamplesAvailable())
    {
        ir.FrontIR =  DRV_ADC_SamplesRead(0);
        ir.SideIR = DRV_ADC_SamplesRead(1);      
    }
    if(ir.ircount == 25)
    {
        IR data = {ir.FrontIR, ir.SideIR};
        SendToIRQueue(data);
        ir.ircount =0;
    }
    ir.ircount++;
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
    irpid.set_distance = distance;
    irpid.enable = true;
    irpid.set_speed = speed;
    irpid.set_dir = dir;
    irpid.integral=0;
    irpid.derivative=0;
    irpid.previous_error=0;
}

void StopIRPID(void)
{
    irpid.enable = false;
    unset = false;
    
}
int GetFrontIR()
{
    return ir.FrontIR;
}
int GetSideIR()
{
    return ir.SideIR;
}
