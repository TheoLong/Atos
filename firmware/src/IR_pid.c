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
IRPID irpid = {0,0,0,0.5,0,0.6,0,FORWARD,false,0,0};
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
            if(irpid.set_dir == BACKWARD)
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
        if(sum0>600 && sum0 <= 813)
        {   
            float diff_voltage = sum0 - 600;        
            float k = diff_voltage/(813 - 600);
            float b = k*40;
            an0_distance = 50-b;
        }
        //2
        if(sum0>420 && sum0 <= 600)
        {
            float diff_voltage = sum0 - 420;        
            float k = diff_voltage/(600 - 420);
            float b = k*50;
            an0_distance = 100-b;
        }
        //3
        if(sum0>345 && sum0 <= 420)
        {
            float diff_voltage = sum0 - 345;        
            float k = diff_voltage/(420 - 345);
            float b = k*50;
            an0_distance = 150-b;
        }
        //4
        if(sum0>285 && sum0 <= 345)
        {
            float diff_voltage = sum0 - 285;        
            float k = diff_voltage/(345 - 285);
            float b = k*50;
            an0_distance = 200-b;
        }
        //5
        if(sum0>240 && sum0 <= 285)
        {
            float diff_voltage = sum0 - 240;        
            float k = diff_voltage/(285 - 240);
            float b = k*50;
            an0_distance = 250-b;
        }
        //6
        if(sum0>215 && sum0 <= 240)
        {
            float diff_voltage = sum0 - 215;        
            float k = diff_voltage/(240 - 215);
            float b = k*50;
            an0_distance = 300-b;
        }
        //7
        if(sum0>185 && sum0 <= 215)
        {
            float diff_voltage = sum0 - 185;        
            float k = diff_voltage/(215 - 185);
            float b = k*50;
            an0_distance = 350-b;
        }
        //8
        if(sum0>185 && sum0 <= 175)
        {
            float diff_voltage = sum0 - 175;        
            float k = diff_voltage/(185 - 175);
            float b = k*50;
            an0_distance = 400-b;
        }
        //-----------------------------------------------------------------------------
        //1
        if(sum2>596 && sum2 <= 789)
        {
            float diff_voltage = sum2 - 596;        
            float k = diff_voltage/(789 - 596);
            float b = k*40;
            an2_distance = 500-b;
        }
        //2
        if(sum2>434 && sum2 <= 596)
        {
            float diff_voltage = sum2 - 434;        
            float k = diff_voltage/(596 - 434);
            float b = k*50;
            an2_distance = 100-b;
        }
        //3
        if(sum2>360 && sum2 <= 434)
        {
            float diff_voltage = sum2 - 360;        
            float k = diff_voltage/(434 - 360);
            float b = k*50;
            an2_distance = 150-b;
        }
        //4
        if(sum2>315 && sum2 <= 360)
        {
            float diff_voltage = sum2 - 315;        
            float k = diff_voltage/(360 - 315);
            float b = k*50;
            an2_distance = 200-b;
        }
        //5
        if(sum2>280 && sum2 <= 315)
        {
            float diff_voltage = sum2 - 280;        
            float k = diff_voltage/(315 - 280);
            float b = k*50;
            an2_distance = 250-b;
        }
        //6
        if(sum2>260 && sum2 <= 280)
        {
            float diff_voltage = sum2 - 260;        
            float k = diff_voltage/(280 - 260);
            float b = k*50;
            an2_distance = 300-b;
        }
        //7
        if(sum2>245 && sum2 <= 260)
        {
            float diff_voltage = sum2 - 245;        
            float k = diff_voltage/(260 - 245);
            float b = k*50;
            an2_distance = 350-b;
        }
        //8
        if(sum2>240 && sum2 <= 245)
        {
            float diff_voltage = sum2 - 240;        
            float k = diff_voltage/(245 - 240);
            float b = k*50;
            an2_distance = 400-b;
        }
        IR data = {sum0, sum2, sum1};
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
    return ir_an2;
}
int GetSideIRF()
{
    
    return ir_an1;
}

int GetSideIRB()
{
    
    return ir_an0;
}