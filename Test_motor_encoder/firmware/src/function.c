#include "Sensor_Control_Thread.h"
#include "Test_Thread.h"

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
