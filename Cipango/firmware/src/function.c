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
    Right_Motor_Distance(FORWARD, 45, 540);
    Left_Motor_Distance(BACKWARD, 45, 540);
    Wait();
}

void Right_Turn()
{
    Right_Motor_Distance(BACKWARD, 45, 540);
    Left_Motor_Distance(FORWARD, 45, 540);
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