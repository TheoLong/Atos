#include "app.h"


void sendToQueue(unsigned int val)
{
    /* Create a queue capable of containing 100 unsigned int values. */
    //xQueue = xQueueCreate( 10, sizeof( unsigned int ) );
    xQueueSend( xQueue1, &val, 100 );
}

void sendToQueueFromISR(unsigned int val)
{
    /* Create a queue capable of containing 100 unsigned int values. */
    //xQueue = xQueueCreate( 10, sizeof( unsigned int ) );
    xQueueSendFromISR( xQueue2, &val, NULL );
}

 //if mode = 0, goes to Pin AN8-15, otherwise goes to Pin 30-37
 void write_port(int mode, uint32_t val)
{
    if(mode)
    {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, val);
    }
    else
    {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, (val << 8));
    }
}