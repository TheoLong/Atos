#include "WiFiReceive.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

WIFIRECEIVE_DATA wifireceiveData;
QueueHandle_t usartreceivequeue;
DRV_HANDLE myUART;
struct MessageStat msgstat = {0, 0, 0, 0, 0};

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************


void WIFIRECEIVE_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    wifireceiveData.state = WIFIRECEIVE_STATE_INIT;
    PLIB_USART_ReceiverInterruptModeSelect(USART_ID_1, USART_RECEIVE_FIFO_ONE_CHAR); 
    PLIB_USART_TransmitterInterruptModeSelect(USART_ID_1, USART_TRANSMIT_FIFO_NOT_FULL); 
    myUART = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);
    usartreceivequeue = xQueueCreate(512, sizeof(char));
    if(usartreceivequeue == NULL)
    {
        //TODO: dbgHLT
    }
}

void WIFIRECEIVE_Tasks ( void )
{
    char strbuf[RECEIVE_BUFFER_SIZE];
    int index = 0;
    /* Check the application's current state. */
    switch ( wifireceiveData.state )
    {
        /* Application's initial state. */
        case WIFIRECEIVE_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                wifireceiveData.state = WIFIRECEIVE_STATE_SERVICE_TASKS;
            }
            break;
        }

        case WIFIRECEIVE_STATE_SERVICE_TASKS:
        {
            while(true)
            {
                char c;
                BaseType_t ret = xQueueReceive(usartreceivequeue, &c, portMAX_DELAY);
                if(ret != pdTRUE)
                {
                    //TODO: dbgHLT
                }
                if(index == 0 && c != '\xFF')
                {
                    continue;
                }
                else if(index >= 255 && c != '\xFF')
                {
                    index = 0;
                }
                else if(index > 4 && c == '\xFF')
                {
                    msgstat.total++;
                    uint8_t ret = CheckString(strbuf, index);
                    if(ret == 0)
                    {
                        struct JsonResponse jsr;
                        uint8_t r = ParseJson(strbuf, &jsr);
                        if(r == 0)
                        {
                            msgstat.missed += jsr.seq - msgstat.sequence - 1;
                            msgstat.sequence = jsr.seq;
                            msgstat.good++;
                            Dispatch(jsr);
                        }
                        else
                        {
                            msgstat.corrupted++;
                        }
                    }
                    else
                    {
                        msgstat.sequence++;
                        msgstat.corrupted++;
                    }
                    index = 0;
                }
                index++;
            }
            break;
        }
        
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void ISR_UART_RECEIVE()
{
    BaseType_t ret, xHigher;
    if(PLIB_USART_ReceiverDataIsAvailable(USART_ID_1))
    {
        char c = PLIB_USART_ReceiverByteReceive(USART_ID_1);
        ret = xQueueSendToBackFromISR(usartreceivequeue, &c, &xHigher);
        if(ret != pdPASS)
        {
            //TODO: dbgHLT
        }
        portEND_SWITCHING_ISR(xHigher);
    }
}


uint8_t CheckString(char * str, int length)
{
    if (length < 10)
    {
        // msgstat.sequence++;
        // msgstat.corrupted++;
        return INCORRECT_FORMAT;
    }
    uint32_t oldhash, newhash;
    memcpy((void*)&oldhash, (void*)(str+1), sizeof(uint32_t));
//    oldhash = ((uint32_t) str[1] << 24) | ((uint32_t) str[2] << 16) 
//            | ((uint32_t) str[3] << 8) | ((uint32_t) str[4]);
    newhash = hash(str + 5);
    if(oldhash != newhash)
    {
        // msgstat.sequence++;
        // msgstat.corrupted++;
        return CHECKSUM_MISMATCH;
    }
    // uint16_t seq;
    // memcpy((void*)&seq, (void*)(str+5), sizeof(uint16_t));
    // if(seq - msgstat.sequence == 1)
    // {
    //     msgstat.sequence++;
    // }
    // else if(seq < msgstat.sequence)
    // {
    //     msgstat.missed += (65535 - msgstat.sequence - 1 + seq);
    //     msgstat.sequence = seq;
    // }
    // else
    // {
    //     msgstat.missed += (msgstat.sequence - seq - 1);
    //     msgstat.sequence = seq;
    // }
    return 0;
}

uint32_t hash(unsigned char * str)
{
	uint32_t hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

uint8_t ParseJson(char * json, struct JsonResponse * j)
{
    json += 5;
    jsmn_parser parser;
	jsmntok_t tokens[32];
	jsmn_init(&parser);
    int r = jsmn_parse(&parser, json, strlen(json), tokens, 32);
	int i;
    if(r < 0)
    {
        return INCORRECT_FORMAT;
    }
	for (i = 1; i < r; i++)
	{
		if (jsoneq(json, &tokens[i], "tsk") == 0)
		{
			j->tsk = atoi(json + tokens[i + 1].start);
        }
        else if (jsoneq(json, &tokens[i], "seq") == 0)
        {
            j->seq = atoi(json + tokens[i + 1].start);
        }
		else if (jsoneq(json, &tokens[i], "0") == 0)
		{
			j->arg0 = atoi(json + tokens[i + 1].start);
		}
		else if (jsoneq(json, &tokens[i], "1") == 0)
		{
			j->arg1 = atoi(json + tokens[i + 1].start);
		}
        else if (jsoneq(json, &tokens[i], "2") == 0)
		{
			j->arg2 = atoi(json + tokens[i + 1].start);
		}
		else if (jsoneq(json, &tokens[i], "3") == 0)
		{
			j->arg3 = atoi(json + tokens[i + 1].start);
        }        
	}
    return 0;  
}

struct MessageStat GetMessageStat()
{
    return msgstat;
}

void Dispatch(struct JsonResponse js)
{
    
}