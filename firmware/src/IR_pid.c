#include "ir_pid.h"
int FrontIR =0;
int SideIRF =0;
int SideIRB =0;
int std_error;
int sum1=0;
int sum2 =0;
int sum0 = 0;
IRPID irpid = {0,0,0,0.1,0.001,0.0001,0,FORWARD,false,0};
IRC ir= {0,0,0,0};
int error;
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
        struct JsonRequest js = {PIC_ID, 's',0, 32,0,ir_distance.Side_IRF,ir_distance.Side_IRB, 0, 0};
        SendOverWiFi(js);
        if(irpid.enable)
        {
            //perform PID here
            error = ir_distance.Side_IRF - ir_distance.Side_IRB - std_error;
            if(irpid.set_dir == FORWARD)
            {
                error = -error;
            }
            //  error = setpoint - measured_value
            irpid.integral = irpid.integral + error*5;
            //  integral = integral + error*dt
            irpid.derivative = (error - irpid.previous_error)/5.0;
            //  derivative = (error - previous_error)/dt
            irpid.output = irpid.Kp*error+ irpid.Ki* irpid.integral+ irpid.Kd*irpid.derivative;
            //  output = Kp*error + Ki*integral + Kd*derivative
            irpid.previous_error = error;
            //  previous_error = error  
            int setl = 0;
            int setr = 0;
            if(irpid.set_speed-irpid.output>50)
            {
                setl = 50;
            }
            if(irpid.set_speed+irpid.output>50)
            {
                setr = 50;
            }
            if(irpid.set_speed-irpid.output<10)
            {
                setl = 10;
            }
            if(irpid.set_speed+irpid.output<10)
            {
                setr = 10;
            }
            else
            {
                setl = irpid.set_speed-irpid.output+0.5;
                setr = irpid.set_speed+irpid.output+0.5;
            }
            Left_Motor_PID(irpid.set_dir,setl); 
            Right_Motor_PID(irpid.set_dir,setr);
            
        }
    }
}

 void ReadIR(void)
{
    sum0=ir_an0+sum0;
    sum1=ir_an1+sum1;
    sum2=ir_an2+sum2;
    if(ir.ircount == 10)
    {
        IR data = {sum0/11, sum2/11, sum1/11};
        SendToIRQueue(data);
        ir.ircount =0;
        sum1=0;
        sum2=0;
        sum0=0;
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
    std_error = sum0/11-sum2/11;
}

void StopIRPID(void)
{
    irpid.enable = false; 
}
int GetFrontIR()
{
    return ir_an1;
}
int GetSideIRF()
{
    return ir_an0;
}

int GetSideIRB()
{
    return ir_an2;
}