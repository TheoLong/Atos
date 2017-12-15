
#include "pixy.h"

#include "app2.h"
#include "public.h"

PixyReport_t PixyReport = {0, 0};
DRV_HANDLE pixy_spi;

void APP2_Initialize ( void )
{
    pixy_spi = DRV_SPI_Open(DRV_SPI_INDEX_1, DRV_IO_INTENT_READWRITE);
}


void APP2_Tasks ( void )
{
    int i;
    while(1)
    {
        uint16_t blueshell = 0, redshell = 0;
        for(i = 0; i < 50;)
        {
            PixyStats_t tempstat = Pixy_GetBlocks(pixy_spi);
            if(tempstat.total_blocks > 0)
            {
                i++;
                blueshell += tempstat.blue;
                redshell += tempstat.red;
            }
        }
        redshell = (redshell + 25) / 50;
        blueshell = (blueshell + 25) / 50;
        PixyReport.blue = blueshell;
        PixyReport.red = redshell;
    }
}

 

/*******************************************************************************
 End of File
 */
