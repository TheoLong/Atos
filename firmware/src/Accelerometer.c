#include "Accelerometer.h"
#include "driver/spi/drv_spi.h"

static PORTS_CHANNEL spi_cs_channel = PORT_CHANNEL_F;
static PORTS_BIT_POS spi_cs_bitPos = PORTS_BIT_POS_12;
short accel_data[3];

void PmodACL_Register_ChipSelect_Pin(PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    spi_cs_channel = channel;
    spi_cs_bitPos = bitPos;
}

void PmodACL_ChipSelect(bool set)
{
    if(set)
        PLIB_PORTS_PinWrite(PORTS_ID_0, spi_cs_channel, spi_cs_bitPos, 0);
    else
        PLIB_PORTS_PinWrite(PORTS_ID_0, spi_cs_channel, spi_cs_bitPos, 1);
}

void PmodACL_Register_Set(DRV_HANDLE spi_handle, uint8_t address, uint8_t value)
{
    DRV_SPI_BUFFER_HANDLE buf1, buf2;
    PmodACL_ChipSelect(true);
    buf1 = DRV_SPI_BufferAddWrite2(spi_handle, &address, sizeof(address), NULL, NULL, &buf2);
    while(DRV_SPI_BufferStatus(buf1) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    buf1 = DRV_SPI_BufferAddWrite2(spi_handle, &value, sizeof(value), NULL, NULL, &buf2);
    while(DRV_SPI_BufferStatus(buf1) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    PmodACL_ChipSelect(false);
}

uint8_t PmodACL_Register_Read(DRV_HANDLE spi_handle, uint8_t address)
{
    address = address | accel_read;
    uint8_t temp = 0;
    DRV_SPI_BUFFER_HANDLE buf;
    PmodACL_ChipSelect(true);
    DRV_SPI_BufferAddWrite2(spi_handle, &address, sizeof(address), NULL, NULL, &buf);
    while(DRV_SPI_BufferStatus(buf) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    DRV_SPI_BufferAddRead2(spi_handle, &temp, sizeof(temp), NULL, NULL, &buf);
    while(DRV_SPI_BufferStatus(buf) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    PmodACL_ChipSelect(false);
    return temp;
}

void PmodACL_Interrupt_Source_Set(DRV_HANDLE spi_handle, uint8_t mask)
{
    PmodACL_Register_Set(spi_handle, addr_INT_ENABLE, mask);
}

void PmodACL_Interupt_Pin_set(DRV_HANDLE spi_handle, uint8_t mask)
{
    PmodACL_Register_Set(spi_handle, addr_INT_MAPPING, mask);
}

void PmodACL_Read_Data(DRV_HANDLE spi_handle, short * data)
{
    uint8_t address = (accel_read | multi_byte | addr_datax0);
    uint8_t raw_data[6];
    DRV_SPI_BUFFER_HANDLE buf;
    PmodACL_ChipSelect(true);
    DRV_SPI_BufferAddWrite2(spi_handle, &address, sizeof(address), NULL, NULL, &buf);
    while(DRV_SPI_BufferStatus(buf) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    DRV_SPI_BufferAddRead2(spi_handle, raw_data, sizeof(raw_data), NULL, NULL, &buf);
    while(DRV_SPI_BufferStatus(buf) != DRV_SPI_BUFFER_EVENT_COMPLETE);
    int i = 0;
    for(i = 0; i < 3; i++)
    {
        data[i] = ((raw_data[i * 2] << 8) | (raw_data[i * 2 + 1]));
    }
    PmodACL_ChipSelect(false);
}

void PmodACL_Init(DRV_HANDLE spi_handle, uint8_t rateout, uint8_t format, uint8_t powermode)
{
    PmodACL_Register_Set(spi_handle, addr_bw_rate ,rateout);
    PmodACL_Register_Set(spi_handle, addr_data_format ,format);
    PmodACL_Register_Set(spi_handle, addr_power_ctl ,powermode);
}