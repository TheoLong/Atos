#ifndef _PIXY_H_
#define _PIXY_H_
#include "app.h"
#include "system_definitions.h"

#define PIXY_START_WORD             0xaa55
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_SYNC_BYTE              0x5a
#define PIXY_SYNC_BYTE_DATA         0x5b

typedef struct
{
    uint16_t signature;
    uint16_t x_center;
    uint16_t y_center;
    uint16_t width;
    uint16_t height;
}PixyBlock_t;

typedef struct
{
    uint8_t total_blocks;
    uint8_t blue;
    uint8_t red;
}PixyStats_t;

int Pixy_GetStart(DRV_HANDLE spi_handle);
uint16_t Pixy_GetWord(DRV_HANDLE spi_handle);
PixyStats_t Pixy_GetBlocks(DRV_HANDLE spi_handle);

#endif