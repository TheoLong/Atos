#include "system_config.h"
#include "system_definitions.h"
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
//my task start here
static void _ReadADC_Tasks (void); 
static void _OutputUART_Tasks (void);
static void _OutputGPIO_Tasks (void);

//reference app task
static void _APP_Tasks(void);

void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 0, NULL);

 
 
    /* Create OS Thread for APP Tasks. */
    xTaskCreate((TaskFunction_t) _APP_Tasks,
                "APP Tasks",
                1024, NULL, 1, NULL);

    //-------------------------------milestone1 task start here----------------------------
    xTaskCreate((TaskFunction_t) _ReadADC_Tasks,"_ReadADC_Tasks",1024, NULL, 1, NULL);
    xTaskCreate((TaskFunction_t)_OutputUART_Tasks, "_OutputUART_Tasks", 1024, NULL, 1, NULL);
    xTaskCreate((TaskFunction_t)_OutputGPIO_Tasks, "_OutputGPIO_Tasks", 1024, NULL, 1, NULL);
    
    vTaskStartScheduler(); /* This function never returns. */
}

void ADC_Initialize ( void )
{
     DRV_ADC_Open();
}

 void TMR_Initialize ( void )
{
     DRV_TMR0_Start();
}

static void _ReadADC_Tasks(void)
{
    while(1)
    {
        if(DRV_ADC_SamplesAvailable())
        {
            int adc_value;
            adc_value = DRV_ADC_SamplesRead(8);
        }
    }
}

static void _OutputUART_Tasks(void)
{
    while(1)
    {
        if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus()) )
        {
            DRV_USART0_WriteByte('g');
        }
    }
}

static void _OutputGPIO_Tasks(void)
{
    while(1)
    {
        
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

static void _APP_Tasks(void)
{
    while(1)
    {
        APP_Tasks();
    }
}

