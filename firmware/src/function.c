#include "public.h"

 void Wait()
{
    while(!Left_Is_Finish() || !Right_Is_Finish())
    {          
    }
}
void Wait_Left()
 {
    while(!Left_Is_Finish())
    {
    }
}

void Wait_Right()
{
    while(!Right_Is_Finish())
    {
    }
}

void Left_Turn()
{
    Right_Motor_Distance(FORWARD, 30, 565);
    Left_Motor_Distance(BACKWARD, 30, 565);
    Wait();
}

void Right_Turn()
{
    Right_Motor_Distance(BACKWARD, 30, 565);
    Left_Motor_Distance(FORWARD, 30, 565);
    Wait();
}

void Move(int speed, int distance, bool dir)
{
    Left_Motor_Distance(dir, speed, distance);
    Right_Motor_Distance(dir, speed, distance);
    Wait();
}

void Wait_Time(int time)
{
     Timing_Wait(time);
    while(!GetTimingFlag())
    {
    }
}

float LinearApprox_an0(int sum0)
{
    float an0_distance=0;
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
     return an0_distance;
}

float LinearApprox_an2(int sum2)
{
    //1
    float an2_distance=0;
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
    return an2_distance;
}