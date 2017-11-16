#include "WiFiTransmit.h"

QueueHandle_t wifitransmitqueue;
QueueHandle_t usarttransmitqueue;
uint16_t picsequence = 0;
uint8_t is_wifi_connected = 0;

void WIFITRANSMIT_Initialize ( void )
{   
    usarttransmitqueue = xQueueCreate(512, sizeof(char));
    wifitransmitqueue = xQueueCreate(16, sizeof(struct JsonRequest));
    if(!wifitransmitqueue || !usarttransmitqueue)
    {
        //TODO: dbgHLT   
    }
}


void WIFITRANSMIT_Tasks ( void )
{
    while(true)
    {
        char str[TRANSMIT_BUFFER_SIZE];
        BaseType_t ret;
        struct JsonRequest js;
        ret = xQueueReceive(wifitransmitqueue, &js, portMAX_DELAY);
        if(ret != pdTRUE)
        {
            //TODO: dbgHLT
        }
        if(is_wifi_connected)
        {
            JsonToString(js, str);
            SendToTransmitQueue(str);
//            picsequence++;
            if((picsequence & 0xF) == 0)
            {
                struct MessageStat msg = GetMessageStat();
                js.seq = 0;
                js.id = PIC_ID;
                js.tgt = 0;
                js.tp = 's';
                js.tsk = 11;
                js.arg0 = msg.total;
                js.arg1 = msg.good;
                js.arg2 = msg.corrupted;
                js.arg3 = msg.missed;
                if(msg.corrupted + msg.missed > 128)
                {
                    //TODO: dbgHLT
                }
                JsonToString(js, str);
                SendToTransmitQueue(str);
//                picsequence++;
            }
        }
        else
        {
            if(GetConnectionStatus())
            {
                is_wifi_connected = 1;
                // js.seq = 0;
                js.id = PIC_ID;
                js.tgt = 0;
                js.tp = 's';
                js.tsk = 10;
                js.arg0 = 0;
                js.arg1 = 0;
                js.arg2 = 0;
                js.arg3 = 0;
                char b[256];
                JsonToString(js, b);
                SendToTransmitQueue(b);
            }
        }
    }
}

 void JsonToString(struct JsonRequest js, char * buf)
 {
     js.seq = picsequence++;
//     js.seq = 0;
     sprintf(buf, "\xFF\x01\x01\x01\x01{\"seq\":%u,\"id\":%u,\"tp\":\"%c\",\"tgt\":%u,"
             "\"tsk\":%u,\"0\":%d,\"1\":%d,\"2\":%d,\"3\":%d}\xFF",
             js.seq, js.id, js.tp, js.tgt, js.tsk, js.arg0, js.arg1, js.arg2, js.arg3);
     uint32_t h = hash(buf+5);
     memcpy((void*)(buf+1), (void*)&h, sizeof(uint32_t));
 }
 
 void SendToTransmitQueue(char * str)
 {
     int index = 0;
     while(str[index] || index < 5)
     {
         BaseType_t ret = xQueueSendToBack(usarttransmitqueue, str+index, portMAX_DELAY);
         if(ret != pdTRUE)
         {
             //TODO: dbgHLT
         }
         index++;
     }
     PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
 }
 
 BaseType_t SendOverWiFi(struct JsonRequest js)
 {
     BaseType_t xHigher;
     BaseType_t ret = xQueueSendToBackFromISR(wifitransmitqueue, &js, &xHigher);
     if(ret != pdPASS)     
     {
         //TODO: dbgHLT
     }
     return xHigher;
     
 }
 
 void ISR_UART_TRANSMIT()
 {
    unsigned char c;
    BaseType_t xHigher;
    BaseType_t ret = xQueueReceiveFromISR(usarttransmitqueue, &c, &xHigher);
    if(ret == pdTRUE)
    {
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
        PLIB_USART_TransmitterByteSend(USART_ID_1, c);
    }
    else
    {
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }     
 }

 uint8_t GetConnectionStatus()
 {
     return (PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0) &&
                PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1));
 }

/*******************************************************************************
 End of File
 */