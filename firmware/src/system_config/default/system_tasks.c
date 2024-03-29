/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "wifireceive.h"
#include "wifitransmit.h"
#include "motor_encoder_thread.h"
#include "control.h"
#include "ir_pid.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
 
 
static void _WIFIRECEIVE_Tasks(void);
static void _WIFITRANSMIT_Tasks(void);
static void _MOTOR_ENCODER_THREAD_Tasks(void);
static void _CONTROL_Tasks(void);
static void _IR_PID_Tasks(void);


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/

void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 0, NULL);

 
 
    /* Create OS Thread for WIFIRECEIVE Tasks. */
    xTaskCreate((TaskFunction_t) _WIFIRECEIVE_Tasks,
                "WIFIRECEIVE Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for WIFITRANSMIT Tasks. */
    xTaskCreate((TaskFunction_t) _WIFITRANSMIT_Tasks,
                "WIFITRANSMIT Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for MOTOR_ENCODER_THREAD Tasks. */
    xTaskCreate((TaskFunction_t) _MOTOR_ENCODER_THREAD_Tasks,
                "MOTOR_ENCODER_THREAD Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for CONTROL Tasks. */
    xTaskCreate((TaskFunction_t) _CONTROL_Tasks,
                "CONTROL Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for IR_PID Tasks. */
    xTaskCreate((TaskFunction_t) _IR_PID_Tasks,
                "IR_PID Tasks",
                1024, NULL, 1, NULL);

    /**************
     * Start RTOS * 
     **************/
    vTaskStartScheduler(); /* This function never returns. */
}


/*******************************************************************************
  Function:
    void _SYS_Tasks ( void )

  Summary:
    Maintains state machines of system modules.
*/
static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */

        /* Maintain Device Drivers */
 
 

        /* Maintain Middleware */

        /* Task Delay */
    }
}

 
 

/*******************************************************************************
  Function:
    void _WIFIRECEIVE_Tasks ( void )

  Summary:
    Maintains state machine of WIFIRECEIVE.
*/

static void _WIFIRECEIVE_Tasks(void)
{
    while(1)
    {
        WIFIRECEIVE_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _WIFITRANSMIT_Tasks ( void )

  Summary:
    Maintains state machine of WIFITRANSMIT.
*/

static void _WIFITRANSMIT_Tasks(void)
{
    while(1)
    {
        WIFITRANSMIT_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _MOTOR_ENCODER_THREAD_Tasks ( void )

  Summary:
    Maintains state machine of MOTOR_ENCODER_THREAD.
*/

static void _MOTOR_ENCODER_THREAD_Tasks(void)
{
    while(1)
    {
        MOTOR_ENCODER_THREAD_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _CONTROL_Tasks ( void )

  Summary:
    Maintains state machine of CONTROL.
*/

static void _CONTROL_Tasks(void)
{
    while(1)
    {
        CONTROL_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _IR_PID_Tasks ( void )

  Summary:
    Maintains state machine of IR_PID.
*/

static void _IR_PID_Tasks(void)
{
    while(1)
    {
        IR_PID_Tasks();
    }
}


/*******************************************************************************
 End of File
 */
