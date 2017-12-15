#include "pixy.h"
#include "driver/spi/drv_spi.h"

int g_skipStart = 0;
int g_blockType = 0;

void Pixy_ChipSelect(bool set)
{
    if(set)
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, 0);
    else
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, 1);
}

uint16_t Pixy_GetWord(DRV_HANDLE spi_handle)
{
    DRV_SPI_BUFFER_HANDLE buf;
    uint16_t w;
//    Pixy_ChipSelect(true);
    DRV_SPI_BufferAddRead2(spi_handle, &w, sizeof(w), NULL, NULL, &buf);
    while(DRV_SPI_BufferStatus(buf) != DRV_SPI_BUFFER_EVENT_COMPLETE);  
//    Pixy_ChipSelect(false);
    return w;
}

int Pixy_GetStart(DRV_HANDLE spi_handle)
{
    uint16_t w, lastw = 0xFFFF;
    while(1)
    {
        w = Pixy_GetWord(spi_handle);
        if(w == 0 && lastw == 0)
        {
            return 0;
        }
        else if(w == PIXY_START_WORD && lastw == PIXY_START_WORD)
        {
            g_blockType = 1;
            return 1;
        }
        else if(w == PIXY_START_WORD_CC && lastw == PIXY_START_WORD)
        {
            g_blockType = 2;
            return 2;
        }
        lastw = w;
    }
}

PixyStats_t Pixy_GetBlocks(DRV_HANDLE spi_handle)
{
    PixyStats_t stat = {0, 0, 0};
    uint16_t checksum, w, sum = 0;
    if(Pixy_GetStart(spi_handle) == 0)
    {
        return stat;
    }
    while(1)
    {
        PixyBlock_t block = {0, 0, 0, 0, 0};
        sum = 0;
        checksum = Pixy_GetWord(spi_handle);
        if(checksum == PIXY_START_WORD || checksum == PIXY_START_WORD_CC || checksum == 0)
        {
            return stat;
        }
        stat.total_blocks++;
        block.signature = Pixy_GetWord(spi_handle);
        block.x_center = Pixy_GetWord(spi_handle);
        block.y_center = Pixy_GetWord(spi_handle);
        block.width = Pixy_GetWord(spi_handle);
        block.height = Pixy_GetWord(spi_handle);
        if(block.signature == 1)
        {
            stat.blue++;
        }
        else if(block.signature == 2)
        {
            stat.red++;
        }
        w = Pixy_GetWord(spi_handle);
        if(w == PIXY_START_WORD || w == PIXY_START_WORD_CC)
            continue;
        else
        {
            return stat; 
        }
    }
}