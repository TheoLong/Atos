#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "public.h"

void APP_Initialize ( void );

void APP_Tasks( void );

void Callback(TimerHandle_t xTimer);

#endif /* _APP_H */


/*******************************************************************************
 End of File
 */

