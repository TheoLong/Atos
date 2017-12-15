#include "app.h"
#include "timers.h"
#include "Accelerometer.h"
#include "queue.h"
#include "pixy.h"

TimerHandle_t PmodACLTimer;
TimerHandle_t ServoTimer1, ServoTimer2, ServoTimer3;
QueueHandle_t ServoQueue;
DRV_HANDLE my_spi;

bool operating = false;
bool load = false;
bool app_initialized = false;
PmodACLData_t ACLData = 
{
    .active = 0,
    .inactive = 0,
    .confidence = 0
};

void APP_Initialize ( void )
{
    TurnOnLEDs(true);
    PmodACL_ChipSelect(false);
    my_spi = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READWRITE);
    DRV_OC0_Start();
    DRV_TMR0_Start();
    ServoTimer1 = xTimerCreate("ServoTimer1", 10, pdTRUE, (void*)0, ServoControlCallback1);
    ServoTimer2 = xTimerCreate("ServoTimer2", 90, pdTRUE, (void*)1, ServoControlCallback2);
    ServoTimer3 = xTimerCreate("ServoTimer3", 500, pdTRUE, (void*)2, ServoControlCallback3);
    PmodACLTimer = xTimerCreate("PmodACLTimer", 125, pdTRUE, (void*)3,PmodACLCallback1);

    ServoQueue = xQueueCreate(128, sizeof(struct JsonResponse));
    if(ServoTimer1 == NULL || ServoQueue == NULL)
    {
        while(1)
        {
            
        }
    }    
}


void APP_Tasks ( void )
{
    if(!app_initialized)
    {
        BaseType_t ret = xTimerStart(ServoTimer1, 5); 
        BaseType_t ret2 = xTimerStart(ServoTimer3, 5);
        if(ret != pdPASS || ret2 != pdPASS)
        {
            ret = pdPASS;
        }        
        PmodACL_Register_Set(my_spi, addr_THRESH_ACT, 0x03);
        PmodACL_Register_Set(my_spi, addr_THRESH_INACT, 0x02);
        PmodACL_Register_Set(my_spi, addr_ACT_INACT_CTL, 0xFF);
        PmodACL_Interrupt_Source_Set(my_spi, INT_ACTIVITY | INT_INACTIVITY);
        PmodACL_Interupt_Pin_set(my_spi, 0x98);
        PmodACL_Init(my_spi, 0x03, 0x09, 0x08);
        app_initialized = true;
    }
    xTimerStart(PmodACLTimer, 5);
    struct JsonResponse jsr;
    while(true)
    {
        BaseType_t ret = xQueueReceive(ServoQueue, &jsr, portMAX_DELAY);
        if(ret == pdTRUE)
        {
            if(jsr.tsk == 79 && jsr.arg3 == 99)
            {
//                xTimerStop(ServoTimer3, 5);
                xTimerStop(ServoTimer2, 5);
                xTimerStop(ServoTimer1, 5);
                xTimerStop(PmodACLTimer, 5);
            }
            if(jsr.tsk == 80 && jsr.arg0 == 1)
            {
                struct JsonRequest jsr = {3, 's', 3, 80, 0, 0, 0, 0, 0};
                SendOverWiFi(jsr);
                load = true;
                DRV_OC0_PulseWidthSet(725);
                vTaskDelay((TickType_t)140);
                xTimerStop(ServoTimer1, 5); 
                xTimerStart(ServoTimer2, 5);            
            }
        }
    }
}

void SendToServoQueue(struct JsonResponse js)
{
    BaseType_t ret = xQueueSendToBack(ServoQueue, (void*)&js, 5);
    if(ret != pdTRUE)
    {
        while(1)
        {
            
        }
    }
}

void ServoControlCallback1(TimerHandle_t xTimer)
{
    operating = true;
    static int pos = 525;
    static bool inc = true;
    if(inc && (pos >= 725))
        inc = false;
    else if(!inc && (pos <=525))
        inc = true;
    DRV_OC0_PulseWidthSet(pos);
    pos = (inc) ? (pos + 5) : (pos - 5);  
    if(ACLData.confidence >= 1)
        TurnOnLEDs(false);
    else
        TurnOnLEDs(true);
}

void ServoControlCallback2(TimerHandle_t xTimer)
{
    operating = true;
    static int pos = 550;
    static int counter = 0;
    if(load)
    {
        load = false;
        counter = 0;
    }
    DRV_OC0_PulseWidthSet(pos);
    pos = (pos == 550) ? 700 : 550;
    if(counter >= 176)
    {
        struct JsonRequest jsr = {3, 's', 0, 80, 0, 0, 0, 0, 0};
        SendOverWiFi(jsr);
        xTimerStop(xTimer, (TickType_t)10);
        xTimerStart(ServoTimer1, (TickType_t)5);
        counter = 0;
    }
    counter++;
    if(ACLData.confidence >= 1)
        TurnOnLEDs(false);
    else
        TurnOnLEDs(true);
}

void ServoControlCallback3(TimerHandle_t xTimer)
{
    struct JsonRequest js = {PIC_ID, 'r', 3, 80, 0, 0, 0, 0, 0};
    SendOverWiFi(js);  
    js.tsk = 79;
    js.tgt = 0;
    SendOverWiFi(js);
    js.tp = 's';
    js.tsk = 100;
    js.arg0 = PixyReport.blue;
    js.arg1 = PixyReport.red;
    SendOverWiFi(js);
    js.tsk = 93;
    if(PixyReport.red > 0 || ACLData.confidence >= 1)
    {
        js.arg0 = 3;
    }
    else if(xTimerIsTimerActive(ServoTimer1) != pdFALSE)
    {
        js.arg0 = 1;
    }
    else if(xTimerIsTimerActive(ServoTimer2) != pdFALSE)
    {
        js.arg0 = 2;
    }
    SendOverWiFi(js);
}

void PmodACLCallback1(TimerHandle_t xTimer)
{
    uint8_t int_source = PmodACL_Register_Read(my_spi, addr_INT_SOURCE);
    if (int_source & 0x10)
    {
        ACLData.active++;
        ACLData.confidence = (ACLData.confidence > 0) ? (ACLData.confidence - 1) : 0;
    }
    else if ((int_source & 0x08) && operating)
    {
        ACLData.confidence = (ACLData.confidence > 2) ? 2 : (ACLData.confidence + 1);
        ACLData.inactive++;
    }
}

void TurnOnLEDs(bool on)
{
    if(on)
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1, 1);
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, 1);
    }
    else
    {
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1, 0);
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3, 0);
    }
}
/*******************************************************************************
 End of File
 */
