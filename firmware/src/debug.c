#include "debug.h"

void dbgOutputVal(unsigned char outVal)
{
    //output anything to  8i/o 
    write_port(1, 120);
}

void dbgUARTVal(unsigned char outVal)
{
    //output anything to UART
    if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus()) )
    {
        DRV_USART0_WriteByte('g');
    }
}

void dbgOutputLoc(unsigned char outVal)
{
    write_port(0,120);
}