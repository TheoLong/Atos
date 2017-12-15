#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_
#include "app.h"
#include "system_definitions.h"

// Accelerometer Port Information
#define accel_spi           SPI_CHANNEL3
#define accel_int1_port     IOPORT_A
#define accel_int2_port     IOPORT_E

// GPIO Interface for Accelerometer Interrupt Pins
#define accel_int1          BIT_7
#define accel_int2          BIT_8

// Accelerometer R/W functions
#define accel_read          0x80
#define multi_byte          0x40

// Accelerometer Data Addresses
#define addr_devid          0x00
#define addr_bw_rate        0x2C
#define addr_power_ctl      0x2D
#define addr_data_format    0x31
#define addr_datax0         0x32
#define addr_INT_ENABLE     0x2E
#define addr_INT_MAPPING    0x2F
#define addr_INT_SOURCE     0x30
#define addr_THRESH_ACT     0x24
#define addr_THRESH_INACT   0x25
#define addr_ACT_INACT_CTL  0x27

#define INT_DATA_READY 0x80
#define INT_SINGLE_TAP 0x40
#define INT_DOUBLE_TAP 0x20
#define INT_ACTIVITY   0x10
#define INT_INACTIVITY 0x08
#define INT_FREE_FALL  0x04
#define INT_WATERMARK  0x02
#define INT_OVERRUN    0x01

void PmodACL_Register_Set(DRV_HANDLE spi_handle, uint8_t address, uint8_t value);
uint8_t PmodACL_Register_Read(DRV_HANDLE spi_handle, uint8_t address);
void PmodACL_Interrupt_Source_Set(DRV_HANDLE spi_handle, uint8_t mask);
void PmodACL_Interupt_Pin_set(DRV_HANDLE spi_handle, uint8_t mask);
void PmodACL_Register_ChipSelect_Pin(PORTS_CHANNEL channel, PORTS_BIT_POS bitPos);
void PmodACL_ChipSelect(bool set);
void PmodACL_Read_Data(DRV_HANDLE spi_handle, short * data);
void PmodACL_Init(DRV_HANDLE spi_handle, uint8_t rateout, uint8_t format, uint8_t powermode);

typedef struct
{
//    short change_abs[3];
//    double change_abs_avg[3];
//    int change_abs_total[3];
//    int change_max[3];
//    int change_min[3];
//    short prev[3];
//    short curr[3];
    int active;
    int inactive;
    int confidence;
//    int count;
}PmodACLData_t;

#endif