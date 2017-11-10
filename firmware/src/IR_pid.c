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
        if(sum0>589 && sum0 <= 867)
        {   
            float diff_voltage = sum0 - 589;        
            float k = diff_voltage/(867 - 589);
            float b = k*40;
            an0_distance = 50-b;
        }
        //2
        if(sum0>430 && sum0 <= 589)
        {
            float diff_voltage = sum0 - 430;        
            float k = diff_voltage/(589 - 430);
            float b = k*50;
            an0_distance = 100-b;
        }
        //3
        if(sum0>345 && sum0 <= 430)
        {
            float diff_voltage = sum0 - 345;        
            float k = diff_voltage/(430 - 345);
            float b = k*50;
            an0_distance = 150-b;
        }
        //4
        if(sum0>291 && sum0 <= 345)
        {
            float diff_voltage = sum0 - 291;        
            float k = diff_voltage/(345 - 291);
            float b = k*50;
            an0_distance = 200-b;
        }
        //5
        if(sum0>253 && sum0 <= 291)
        {
            float diff_voltage = sum0 - 253;        
            float k = diff_voltage/(291 - 253);
            float b = k*50;
            an0_distance = 250-b;
        }
        //6
        if(sum0>222 && sum0 <= 253)
        {
            float diff_voltage = sum0 - 222;        
            float k = diff_voltage/(253 - 222);
            float b = k*50;
            an0_distance = 300-b;
        }
        //7
        if(sum0>200 && sum0 <= 222)
        {
            float diff_voltage = sum0 - 200;        
            float k = diff_voltage/(222 - 200);
            float b = k*50;
            an0_distance = 350-b;
        }
        //8
        if(sum0>195 && sum0 <= 200)
        {
            float diff_voltage = sum0 - 195;        
            float k = diff_voltage/(200 - 195);
            float b = k*35;
            an0_distance = 385-b;
        }
        //-----------------------------------------------------------------------------
        //1
        if(sum2>582 && sum2 <= 840)
        {
            float diff_voltage = sum2 - 582;        
            float k = diff_voltage/(840 - 582);
            float b = k*40;
            an2_distance = 50-b;
        }
        //2
        if(sum2>428 && sum2 <= 582)
        {
            float diff_voltage = sum2 - 428;        
            float k = diff_voltage/(582 - 428);
            float b = k*50;
            an2_distance = 100-b;
        }
        //3
        if(sum2>345 && sum2 <= 428)
        {
            float diff_voltage = sum2 - 345;        
            float k = diff_voltage/(428 - 345);
            float b = k*50;
            an2_distance = 150-b;
        }
        //4
        if(sum2>296 && sum2 <= 345)
        {
            float diff_voltage = sum2 - 296;        
            float k = diff_voltage/(345 - 296);
            float b = k*50;
            an2_distance = 200-b;
        }
        //5
        if(sum2>261 && sum2 <= 296)
        {
            float diff_voltage = sum2 - 261;        
            float k = diff_voltage/(296 - 261);
            float b = k*50;
            an2_distance = 250-b;
        }
        //6
        if(sum2>239 && sum2 <= 261)
        {
            float diff_voltage = sum2 - 239;        
            float k = diff_voltage/(261 - 239);
            float b = k*50;
            an2_distance = 300-b;
        }
        //7
        if(sum2>220 && sum2 <= 239)
        {
            float diff_voltage = sum2 - 220;        
            float k = diff_voltage/(239 - 220);
            float b = k*50;
            an2_distance = 350-b;
        }
        //8
        if(sum2>213 && sum2 <= 220)
        { 
            float diff_voltage = sum2 - 213;        
            float k = diff_voltage/(220 - 213);
            float b = k*35;
            an2_distance = 385-b;
        }
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