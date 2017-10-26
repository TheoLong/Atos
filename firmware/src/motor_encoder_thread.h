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
#include "queue.h"
#include "timers.h"
#include <math.h>
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

struct Encoder_Struct 
{
    int Encoder_Left_Speed;
    int Encoder_Right_Speed;
};

typedef struct Encoder_Struct Encoder;
void MOTOR_ENCODER_THREAD_Initialize ( void );
void MOTOR_ENCODER_THREAD_Tasks( void );
void Read_Encoders(void);
void SendToQueue(Encoder data);
int Left_PID_module(int Speed, int set_speed, int*pwm);
int Right_PID_module(int Speed, int set_speed, int*pwm);
QueueHandle_t Encoder_Q;
typedef struct PID 
{
    int integral;
    int previous_error;
    double derivative;
    double Kp;
    double Ki;
    double Kd;
    int speed;
    bool dir;
    int pwm;
} PID;

typedef struct DISTANCE_CONTROL
{
    int old_distance;
    int current_distance;
    int move_distance;
}DISTANCE_CONTROL;

typedef struct FLAG
{
    bool distance_mode;
    bool left_finish;
    bool right_finish;
    bool time_up;
    bool counter_start;
}FLAG;

typedef struct TIME_CONTROL
{
    int set_time;
    int counter;
}TIME_CONTROL;

typedef struct SERVO
{
    int pwm;
}SERVO;

#endif /* _MOTOR_ENCODER_THREAD_H */

#ifdef __cplusplus
}
#endif
