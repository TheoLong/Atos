#include "motor_encoder_thread.h"
uint32_t Left_Encoder_data = 1;
uint32_t Right_Encoder_data = 1;
//
void MOTOR_ENCODER_THREAD_Initialize ( void )
{
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    //DRV_OC0_Enable();
    DRV_OC0_Start();
    //DRV_OC1_Enable();
    DRV_OC1_Start();
    //init pins for motor dir
    
}


void MOTOR_ENCODER_THREAD_Tasks ( void )
{
    Motor_Left_Set(BACKWARD, 75);
    Motor_Right_Set(BACKWARD, 75);
}

void Motor_Left_Set(bool dir, int pwm)
{
    //direction pin set
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, 1, dir);
    //set pwm
    DRV_OC1_PulseWidthSet(pwm);
}
void Motor_Right_Set(bool dir, int pwm)
{
    //direction pin set
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, 14, dir);
    //set pwm
    DRV_OC0_PulseWidthSet(pwm);
}

void Read_Encoders(void)
{
    Left_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_3);
    Right_Encoder_data = PLIB_TMR_Counter16BitGet(TMR_ID_4);
    
}