#ifndef _MOTOR_ENCODER_THREAD_H
#define _MOTOR_ENCODER_THREAD_H

// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

#define FORWARD false
#define BACKWARD true


void MOTOR_ENCODER_THREAD_Initialize ( void );
void MOTOR_ENCODER_THREAD_Tasks( void );
void Motor_Left_Set(bool dir, int pwm);
void Motor_Right_Set(bool dir, int pwm);
void Read_Encoders(void);

#endif /* _MOTOR_ENCODER_THREAD_H */

#ifdef __cplusplus
}
#endif

