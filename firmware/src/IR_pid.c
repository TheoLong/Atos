#include "ir_pid.h"
int FrontIR =0;
int SideIRF =0;
int SideIRB =0;
IRPID irpid = {0,0,0,0.8,0.05,0.01,0,FORWARD,false,0};
IRC ir= {0,0,0,0};
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
    IR ir_distance = {0, 0, 0};
    
    BaseType_t ret = xQueueReceive(ir_q, &ir_distance, (TickType_t) 5);
    if(ret == pdFALSE)
    {
        
    }
    else
    {
        SideIRF=ir_distance.Side_IRF;
        SideIRB=ir_distance.Side_IRB;
        if(irpid.enable)
        {
            //perform PID here
            int error = ir_distance.Side_IRF - ir_distance.Side_IRB;
            //  error = setpoint - measured_value
            irpid.integral = irpid.integral + error*5;
            //  integral = integral + error*dt
            irpid.derivative = (error - irpid.previous_error)/5.0;
            //  derivative = (error - previous_error)/dt
            irpid.output = irpid.Kp*error+ irpid.Ki* irpid.integral+ irpid.Kd*irpid.derivative;
            //  output = Kp*error + Ki*integral + Kd*derivative
            irpid.previous_error = error;
            //  previous_error = error  
            Left_Motor_PID(irpid.set_dir,irpid.set_speed-irpid.output); 
            Right_Motor_PID(irpid.set_dir,irpid.set_speed+irpid.output);
            //struct JsonRequest js = {PIC_ID, 's',0, 32,0,ir_distance.Side_IRF,ir_distance.Side_IRB, irpid.output, 0};
            //SendOverWiFi(js);
        }
    }
}

 void ReadIR(void)
{
    if(ir.ircount == 25)
    {
        IR data = {ir_an0, ir_an1, ir_an2};
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

void SetIRPID(bool dir, int speed)
{
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
}
int GetFrontIR()
{
    return ir.FrontIR;
}
int GetSideIRF()
{
    return ir.SideIRF;
}

int GetSideIRB()
{
    return ir.SideIRB;
}