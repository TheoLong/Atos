#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "debug.h"
// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
//my task start here
static void _Output_Tasks (void);


void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 0, NULL);
    //-------------------------------milestone1 task start here----------------------------
    xQueue1 = xQueueCreate( 10, sizeof( unsigned int ) );
    xQueue2 = xQueueCreate( 10, sizeof( unsigned int ) );
    
    xTaskCreate((TaskFunction_t)_Output_Tasks, "_Output_Tasks", 1024, NULL, 1, NULL);
    
    vTaskStartScheduler(); /* This function never returns. */
}

static void _Output_Tasks(void)
{
    while(1)
    {
        if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus()) )
        {
            sendToQueue('a');
            char c = 0;
            xQueueReceive(xQueue1, &c, portMAX_DELAY); 
            DRV_USART0_WriteByte(c);
        }
        
       //sent some number 
        sendToQueue('g');
        unsigned int i;
        xQueueReceive(xQueue1, &i, portMAX_DELAY); 
        write_port(1, i);
    }
}


static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */

        /* Maintain Device Drivers */
    DRV_USART_TasksTransmit(sysObj.drvUsart0);
    DRV_USART_TasksError (sysObj.drvUsart0);
    DRV_USART_TasksReceive(sysObj.drvUsart0);
        /* Maintain Middleware */

        /* Task Delay */
    }
}

