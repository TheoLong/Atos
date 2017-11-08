#include "app.h"

volatile int ir_an0, ir_an1, ir_an2;

void APP_Initialize ( void )
{
    DRV_ADC_Open();
    DRV_ADC_Start();
}


void APP_Tasks ( void )
{
    if(ir_an0 || ir_an1 || ir_an2)
    {
        //WTF
        printf("Good\n!");
    }
}

 

/*******************************************************************************
 End of File
 */
