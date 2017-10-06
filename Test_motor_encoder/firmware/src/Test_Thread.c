#include "test_thread.h"

void TEST_THREAD_Initialize ( void )
{
  
}


void TEST_THREAD_Tasks ( void )
{
    //
    //Right_Motor_Distance(BACKWARD, 45, 550);
    Left_Motor_Distance(FORWARD, 45, 550);
    Right_Motor_Distance(FORWARD, 45, 550);
//    while(!Left_Is_Finish() || !Right_Is_Finish())
//    {          
//    }
    Wait();
    Right_Motor_Distance(FORWARD, 45, 550);
//    while(!Right_Is_Finish())
//    {
//    }
    Wait_Right();
    Left_Motor_Distance(BACKWARD, 45, 550);
    while(!Left_Is_Finish())
    {
    }
    
    
}


/*******************************************************************************
 End of File
 */
