/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "system/common/sys_common.h"
#include "wifireceive.h"
#include "wifitransmit.h"
#include "motor_encoder_thread.h"
#include "control.h"
#include "ir_pid.h"
#include "system_definitions.h"
#include "public.h"
#include "statemachine.h"

int bumper = 0;
int ir_an0, ir_an1, ir_an2;
// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void IntHandlerDrvUsartInstance0(void)
{
   if(PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT))
    {
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        ISR_UART_TRANSMIT();
    }
    if(PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE))
    {
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        ISR_UART_RECEIVE();
    }    
}
 
void IntHandlerDrvAdc(void)
{
    /* Clear ADC Interrupt Flag */
    ir_an0 = (PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 0)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 3)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 6)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 9))/4;
    ir_an1 = (PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 1)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 4)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 7)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 10))/4;
    ir_an2 = (PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 2)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 5)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 8)+PLIB_ADC_ResultGetByIndex(DRV_ADC_ID_1, 11))/4;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_ADC_1);
}

void IntHandlerExternalInterruptInstance0(void)
{
    struct JsonResponse js = {61, 1, 1, 1, 1};
    SendToControlQueue(js);
//    smp.bumper = true;
    struct JsonRequest jsr = {PIC_ID, 's', PIC_ID, 65, 0, 5, 5, 5, 5};
    SendOverWiFi(jsr);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_3);
}
 

void IntHandlerDrvTmrInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
}

void IntHandlerDrvTmrInstance1(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_5);
}

void IntHandlerDrvTmrInstance2(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_4);
}

void IntHandlerDrvTmrInstance3(void)
{
    //50hz timer
    static count = 0;
    ReadIR();
    //10hz
    if(count < 5)
    {
        count++;
    }
    else
    {
        count = 0;
        Read_Encoders();
    }
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
}
 
/*******************************************************************************
 End of File
*/