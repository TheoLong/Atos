
//include these files in order to use PLIB_PORTS API calls
#include <xc.h> //may or may not be required
#include <peripheral/ports/plib_ports.h>

void init_pins( void );

void write_port(int mode, uint32_t val);

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
}
