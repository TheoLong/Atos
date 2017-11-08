#ifndef _APP_H
#define _APP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "system_config.h"
#include "system_definitions.h"

extern volatile int ir_an0, ir_an1, ir_an2;

void APP_Initialize ( void );

void APP_Tasks( void );

#endif
