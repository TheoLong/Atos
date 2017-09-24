#ifndef _SENSOR_CONTROL_THREAD_H
#define _SENSOR_CONTROL_THREAD_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

void SENSOR_CONTROL_THREAD_Initialize ( void );
void SENSOR_CONTROL_THREAD_Tasks( void );


#endif /* _SENSOR_CONTROL_THREAD_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


