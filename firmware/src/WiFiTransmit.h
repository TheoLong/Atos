#ifndef _WIFITRANSMIT_H
#define _WIFITRANSMIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
#include "public.h"

#define TRANSMIT_BUFFER_SIZE 256
#define STAT_SEND_FREQ 0x1F

void WIFITRANSMIT_Initialize ( void );

void WIFITRANSMIT_Tasks( void );

void JsonToString(struct JsonRequest js, char * buf);

void SendToTransmitQueue(char * str);

void ISR_UART_TRANSMIT();

#endif
/*******************************************************************************
 End of File
 */

