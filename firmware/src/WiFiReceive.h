/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    wifireceive.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _WIFIRECEIVE_H
#define _WIFIRECEIVE_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

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
#define WIFI_REPORT_RATE 0

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

void SendMessageStat(struct JsonRequest * js);

void Dispatch(struct JsonResponse js);

#endif /* _WIFIRECEIVE_H */


/*******************************************************************************
 End of File
 */

