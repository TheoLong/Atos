/* ************************************************************************** */

#include "app_public.h"
#include "debug.h"

/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

void dbgHalt(uint8_t reason)
{
    SYS_INT_StatusGetAndDisable();
    dbgOutputLoc(reason);
    dbgOutputLoc(reason);
    while(1)
    {
        
    }
}

void dbgOutputVal(unsigned char outVal)
{
    write_port(PIN30_37, (uint32_t) outVal);
}

void dbgUARTVal(unsigned char outVal)
{
    sendToUART(outVal);
}


void dbgOutputLoc(unsigned char outVal)
{
    write_port(PINAN8_15, (uint32_t) outVal);
}

/* *****************************************************************************
 End of File
 */
