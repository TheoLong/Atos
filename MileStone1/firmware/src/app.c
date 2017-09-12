/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "app_public.h"
#include "debug.h"
#include "driver/tmr/drv_tmr_mapping.h"
#include "queue.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

QueueHandle_t myAppQueue;
DRV_HANDLE myUART;
SYS_MODULE_OBJ myTMR0;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    myUART = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);

    myTMR0 = DRV_TMR_Open(DRV_TMR_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
    
    uint32_t DesiredF = 4;
    uint32_t ActualF = DRV_TMR_CounterFrequencyGet(myTMR0);
    uint32_t divider = ActualF / DesiredF;
    
    DRV_TMR_AlarmRegister(myTMR0, divider, true, 0, ISR_Timer);
    
    DRV_TMR_Start(myTMR0);
    DRV_ADC_Open();
    DRV_ADC_Start();
    
    myAppQueue = xQueueCreate( 10, sizeof( uint32_t ) );
    if(!myAppQueue)
    {
        dbgHalt(HALTED_QUEUE_CREATE);
    }
    init_pins();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    dbgOutputLoc(TASK_ENTER);
    BaseType_t ret;
    uint32_t val;
    dbgOutputLoc(TASK_LOOP_ENTER);
    while(1)
    {
        dbgOutputLoc(TASK_QUEUE_BEFORE_RECEIVE);
        ret = xQueueReceive(myAppQueue, (void*) &val, portMAX_DELAY);
        dbgOutputLoc(TASK_QUEUE_AFTER_RECEIVE);
        if(ret == pdFALSE)
        {
            dbgHalt(HALTED_QUEUE_RECEIVE);
        }
        dbgOutputVal(val);
        dbgUARTVal(val);
//        sendToUART(val);
//        write_port(PIN30_37, val);
    }
}



uint16_t getVoltage(uint16_t raw)
{
    return (raw * 10000 + 5120) / 10240 * 33;
//    return v;
}
 
void ISR_Timer (uintptr_t context, uint32_t alarmCount)
{
    dbgOutputLoc(ISR_ENTER);
    uint16_t i = 0;
    if(DRV_ADC_SamplesAvailable)
        i = DRV_ADC_SamplesRead(0);
    uint16_t v = getVoltage(i) / 100;
    dbgOutputLoc(ISR_QUEUE_BEFORE_SEND);
    sendToAppQueue((uint32_t)v);
    dbgOutputLoc(ISR_QUEUE_AFTER_SEND);
    dbgOutputLoc(ISR_EXIT);
//    sendToUART((v >> 8));
//    sendToUART((char)(v & 0xFF));
}

void sendToAppQueue(uint32_t val)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t r = xQueueSendFromISR(myAppQueue, &val, &xHigherPriorityTaskWoken);
    if(r == errQUEUE_FULL)
    {
        dbgHalt(HALTED_QUEUE_SEND);
    }
}

void sendToUART(uint8_t byte)
{
    if(!DRV_USART_TransmitBufferIsFull(myUART))
        DRV_USART_WriteByte(myUART, byte);    
}

void init_pins( void )
{
    //pin A8-A15
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_8, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_9, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_10, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_11, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_12, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_13, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_14, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModeSelect (PORTS_ID_0, PORTS_ANALOG_PIN_15, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_DirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_B, 0xFF00);
    //pin 8-15
    PLIB_PORTS_DirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_A, 0x000C);
    PLIB_PORTS_DirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_D, 0x1018);
    PLIB_PORTS_DirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_F, 0x3000);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4);
    //pin 30-37
    PLIB_PORTS_DirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    
    //LEDs for testing only
    //PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
    //PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1);
}

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
/*******************************************************************************
 End of File
 */
