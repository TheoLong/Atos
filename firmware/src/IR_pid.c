#include "ir_pid.h"
int FrontIR =0;
int SideIRF =0;
int SideIRB =0;
int std_error;
int sum1=0;
float sum2 =0;
float sum0 = 0;
float an0_distance =0;
float an2_distance =0;
IRPID irpid = {0,0,0,0.2,0,0.2,0,FORWARD,false,0,0};
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
            irpid.derivative = ir_distance.Side_IRF - ir_distance.Side_IRB;
            error = (ir_distance.Side_IRF + ir_distance.Side_IRB)/2 - irpid.distance;
            if(irpid.set_dir == FORWARD)
            {
                irpid.derivative = -irpid.derivative;
            }
            //  error = setpoint - measured_value
            irpid.integral = irpid.integral + error;
            //  integral = integral + error*dt
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
            else if(irpid.set_speed-irpid.output<10)
            {
                setl = 10;
            }
            else
            {
                setl = irpid.set_speed+irpid.output;
                setr = irpid.set_speed-irpid.output;
            }
            if(irpid.set_speed+irpid.output>50)
            {
                setr = 50;
            }
            else if(irpid.set_speed+irpid.output<10)
            {
                setr = 10;
            }
            else
            {
                setl = irpid.set_speed+irpid.output;
                setr = irpid.set_speed-irpid.output;
            }
            Left_Motor_PID(irpid.set_dir,setl); 
            Right_Motor_PID(irpid.set_dir,setr);
        }
    }
}

 void ReadIR(void)
{
    sum0=ir_an0+sum0;
    sum2=ir_an2+sum2;
    //
    if(ir.ircount == 10)
    {
        sum0 = sum0/11;
        sum1=sum1/11;
        sum2=sum2/11;
        //1
        an0_distance = LinearApprox_an0(sum0);
        an2_distance = LinearApprox_an2(sum2);
        IR data = {an0_distance, an2_distance, sum1};
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

void SetIRPID(bool dir, int speed, int distance)
{
    irpid.enable = true;
    irpid.set_speed = speed;
    irpid.set_dir = dir;
    irpid.integral=0;
    irpid.derivative=0;
    irpid.previous_error=0;
    irpid.distance = distance;
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