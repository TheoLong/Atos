#include "system_config.h"
#include "system_definitions.h"

// <editor-fold defaultstate="collapsed" desc="Configuration Bits">

/*** DEVCFG0 ***/

#pragma config DEBUG =      ON
#pragma config ICESEL =     ICS_PGx2
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      FRCPLL
#pragma config FSOSCEN =    ON
#pragma config IESO =       ON
#pragma config POSCMOD =    OFF
#pragma config OSCIOFNC =   OFF
#pragma config FPBDIV =     DIV_8
#pragma config FCKSM =      CSECMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLIDIV =   DIV_2
#pragma config UPLLEN =     OFF
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FMIIEN =     ON
#pragma config FETHIO =     ON
#pragma config FCANIO =     ON
#pragma config FUSBIDIO =   ON
#pragma config FVBUSONIO =  ON
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_Timer Initialization Data">
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_USART Initialization Data">
// </editor-fold>

SYSTEM_OBJECTS sysObj;

//-----------------------------------init----------------------------------------
void GPIO_ADC_TMR_init( void )
{
    DRV_ADC_Open();
    DRV_TMR0_Start();
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

void SYS_Initialize ( void* data )
{
    /* Core Processor Initialization */
    SYS_CLK_Initialize( NULL );
    SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)NULL);
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
    SYS_DEVCON_JTAGDisable();
    SYS_PORTS_Initialize();

    /* Initialize Drivers */

    /* Initialize ADC */
    DRV_ADC_Initialize();

    /*Initialize TMR0 */
    DRV_TMR0_Initialize();
 
     sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)NULL);

    /* Initialize System Services */

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();

    /* Initialize Middleware */

    /* Initialize the Application */
    GPIO_ADC_TMR_init();
}


/*******************************************************************************
 End of File
*/

