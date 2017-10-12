#include "test_thread.h"

void TEST_THREAD_Initialize ( void )
{
}


void TEST_THREAD_Tasks ( void )
{
    //Left_Turn();
    //Right_Turn();
//    Timing_Wait(800);
//    while(!GetTimingFlag())
//    {
//    }
    SetServo2PWM(770);
    Wait_Time(800);
    SetServo2PWM(0);
    Wait_Time(800);
    SetServo2PWM(50);
    Wait_Time(800);
    SetServo2PWM(0);
    Wait_Time(800);
    //speed, distance, dir
    //Move(45, 1500, FORWARD);
    
    
}

/*******************************************************************************
 End of File
 */
