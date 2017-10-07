#include "test_thread.h"

void TEST_THREAD_Initialize ( void )
{
  
}


void TEST_THREAD_Tasks ( void )
{
    Left_Turn();
    Right_Turn();
    //speed, distance, dir
    Move(45, 1500, FORWARD);
    
    
}


/*******************************************************************************
 End of File
 */
