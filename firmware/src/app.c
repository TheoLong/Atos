#include "app.h"
#include "debug.h"

APP_DATA appData;

void put_in_que(unsigned int val)
{
    /* Create a queue capable of containing 100 unsigned int values. */
    xQueue = xQueueCreate( 10, sizeof( unsigned int ) );
    xQueueSend( xQueue, &val, 100 );
}

void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;
    //test freertos 
    //put_in_que(512);
}

void APP_Tasks ( void )
{
    switch(appData.state)
    {
        case APP_STATE_INIT:
        {
            DRV_ADC_Open();
            DRV_TMR0_Start();
            appData.state = APP_STATE_NORMAL;
            break; 
        }
        case APP_STATE_NORMAL:
        {
            if(DRV_ADC_SamplesAvailable())
            {
                appData.ADC_data_value = DRV_ADC_SamplesRead(8);
            }
            break;
        }
        case APP_STATE_UART:
        {
              //set up uart to send this value to computer
            if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus()) )
            {
//                int output_8 = appData.ADC_data_value >> 2;
//                int first = (output_8/100)|0x30;
//                int second = ((output_8-(output_8/100)*100)/10) |0x30;
//                char thrid = (output_8-(output_8/10)*10) |0x30;
//                DRV_USART0_WriteByte(first);  // send modified byte
//                DRV_USART0_WriteByte(second);
//                DRV_USART0_WriteByte(thrid);
                DRV_USART0_WriteByte('g');
                appData.state = APP_STATE_NORMAL;
            }
            break;
        }
        default:
        {
            
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
