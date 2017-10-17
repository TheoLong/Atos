#ifndef _WIFIRECEIVE_H
#define _WIFIRECEIVE_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
#include <peripheral/usart/plib_usart.h>
#include "public.h"
#include "jsmn.h"

#define RECEIVE_BUFFER_SIZE 256

#define INCORRECT_FORMAT 1
#define CHECKSUM_MISMATCH 2

typedef enum
{
	/* Application's state machine's initial state. */
	WIFIRECEIVE_STATE_INIT=0,
	WIFIRECEIVE_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} WIFIRECEIVE_STATES;

typedef struct
{
    /* The application's current state */
    WIFIRECEIVE_STATES state;

    /* TODO: Define any additional data used by the application. */

} WIFIRECEIVE_DATA;

void WIFIRECEIVE_Initialize ( void );

void WIFIRECEIVE_Tasks( void );

void ISR_UART_RECEIVE();

uint8_t CheckString(char * str, int length);

uint8_t ParseJson(char * str, struct JsonResponse * js);

void Dispatch(struct JsonResponse js);

#endif /* _WIFIRECEIVE_H */

