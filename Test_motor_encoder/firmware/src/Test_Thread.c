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
    SetServoPWM(770);
    Timing_Wait(800);
    while(!GetTimingFlag())
    {
    }
    SetServoPWM(0);
    Timing_Wait(800);
    while(!GetTimingFlag())
    {
    }
    SetServoPWM(50);
    Timing_Wait(800);
    while(!GetTimingFlag())
    {
    }
    SetServoPWM(0);
    Timing_Wait(800);
    while(!GetTimingFlag())
    {
    }
    //speed, distance, dir
    //Move(45, 1500, FORWARD);
    
    
}

/*******************************************************************************
 End of File
 */
