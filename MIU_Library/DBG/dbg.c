/**
  ******************************************************************************
  * @file           : dbg.c
  * @brief          : Functions for debug task
  ******************************************************************************
  * @attention
  * @PIC: muhammad.ahmad@georgekent.net
  * @Authors:
  *   18 Dec 2020	muhammad.ahmad@georgekent.net – Original version
  *   15 Oct 2025	yee-kong.chong@georgekent.net – Updated version
  *
  * @Copyright: George Kent (Malaysia) Berhad.
  * 
  ******************************************************************************
**/
/* Private includes ----------------------------------------------------------*/
#include "dbg.h"
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static USART_TypeDef* dbg_uart = NULL;

static uint16_t uwHead[DBG_CFG_NO_OF_CHANNEL]= {0, 0};
static uint16_t uwTail[DBG_CFG_NO_OF_CHANNEL]= {0, 0};
static uint8_t  pucBuf[DBG_CFG_NO_OF_CHANNEL][DBG_CFG_BUF_SIZE];

#define CHANNEL_MARKER_INDEX 6 					//after "<gcom"
static char pcChannelMarker[]= "\n<gLog0>:\n";	//space added in front cos sometimes to overcome nbiot initial noise
static uint8_t pcChannelMarkerLen= sizeof(pcChannelMarker) - 1;
static char *pChannel;
static uint8_t cChannelInd;


/**
  * @brief: Initialize for main application
  * @PIC: Ricky Siah
  * @param: None
  * @retval: None
  */
void DBG_Init(USART_TypeDef* uart_instance)
{
    // Store the handle to the initialized UART peripheral.
    dbg_uart = uart_instance;

    pChannel= pcChannelMarker+ CHANNEL_MARKER_INDEX;
	*pChannel= DBG_CHANNEL_DBG_IND;

    // Ensure UART is enabled. This is a safe check.
    // The peripheral should already be configured and enabled by the application.
    if ((dbg_uart->CR1 & USART_CR1_UE) == 0)
    {
    	LL_USART_Enable(dbg_uart);
    }
}

void DBG_Task(void)
{
    bool _sendData= false;
	uint8_t _data;

	if(true== LL_USART_IsActiveFlag_TC(dbg_uart))
	{
		if(pcChannelMarkerLen!= cChannelInd)
		{
			_data= pcChannelMarker[cChannelInd++];
			_sendData= true;
		}
		else
		{
			switch(*pChannel)
			{
				case DBG_CHANNEL_COM_IND:
					if(uwHead[DBG_CHANNEL_COM]!= uwTail[DBG_CHANNEL_COM])
					{
						_data=  pucBuf[DBG_CHANNEL_COM][uwHead[DBG_CHANNEL_COM]++% DBG_CFG_BUF_SIZE];
						_sendData= true;
					}
					else if(uwHead[DBG_CHANNEL_SNF]!= uwTail[DBG_CHANNEL_SNF])
					{
						*pChannel= DBG_CHANNEL_SNF_IND;
						cChannelInd= 0;
					}
					else if(uwHead[DBG_CHANNEL_DBG]!= uwTail[DBG_CHANNEL_DBG])
					{
						*pChannel= DBG_CHANNEL_DBG_IND;
						cChannelInd= 0;
					}
					break;

				case DBG_CHANNEL_SNF_IND:
					if(uwHead[DBG_CHANNEL_SNF]!= uwTail[DBG_CHANNEL_SNF])
					{
						_data=  pucBuf[DBG_CHANNEL_SNF][uwHead[DBG_CHANNEL_SNF]++% DBG_CFG_BUF_SIZE];
						_sendData= true;
					}
					else if(uwHead[DBG_CHANNEL_COM]!= uwTail[DBG_CHANNEL_COM])
					{
						*pChannel= DBG_CHANNEL_COM_IND;
						cChannelInd= 0;
					}
					else if(uwHead[DBG_CHANNEL_DBG]!= uwTail[DBG_CHANNEL_DBG])
					{
						*pChannel= DBG_CHANNEL_DBG_IND;
						cChannelInd= 0;
					}
					break;

				case DBG_CHANNEL_DBG_IND:
					if(uwHead[DBG_CHANNEL_DBG]!= uwTail[DBG_CHANNEL_DBG])
					{
						_data=  pucBuf[DBG_CHANNEL_DBG][uwHead[DBG_CHANNEL_DBG]++% DBG_CFG_BUF_SIZE];
						_sendData= true;
					}
					else if(uwHead[DBG_CHANNEL_COM]!= uwTail[DBG_CHANNEL_COM])
					{
						*pChannel= DBG_CHANNEL_COM_IND;
						cChannelInd= 0;
					}
					else if(uwHead[DBG_CHANNEL_SNF]!= uwTail[DBG_CHANNEL_SNF])
					{
						*pChannel= DBG_CHANNEL_SNF_IND;
						cChannelInd= 0;
					}
					break;
			}
		}

		if(true== _sendData)
		{
			LL_USART_TransmitData8(dbg_uart, _data);
		}
		//LOG_DisableSleep(!_sendData);
	}
}

__INLINE void DBG_COM_PutByte(uint8_t _byte)
{
	pucBuf[DBG_CHANNEL_COM][uwTail[DBG_CHANNEL_COM]++% DBG_CFG_BUF_SIZE]= _byte;
}

__INLINE void DBG_SNF_PutByte(uint8_t _byte)
{
	pucBuf[DBG_CHANNEL_SNF][uwTail[DBG_CHANNEL_SNF]++% DBG_CFG_BUF_SIZE]= _byte;
}

__INLINE void DBG_DBG_PutByte(uint8_t _byte)
{
	pucBuf[DBG_CHANNEL_DBG][uwTail[DBG_CHANNEL_DBG]++% DBG_CFG_BUF_SIZE]= _byte;
}

void DBG_COM_PutString(char* _string)
{
	while(*_string!= 0)
	{
		DBG_COM_PutByte((uint8_t)(*_string++));
	}
}

void DBG_SNF_PutString(char* _string)
{
	while(*_string!= 0)
	{
		DBG_SNF_PutByte((uint8_t)(*_string++));
	}
}

void DBG_DBG_PutString(char* _string)
{
	while(*_string!= 0)
	{
		DBG_DBG_PutByte((uint8_t)(*_string++));
	}
}


void DBG_DBG_PutNumber(uint32_t _uint32)//2^32=4294967296
{
	bool _leadingZero= true;
	uint32_t _decimal= 1000000000;
	uint8_t _digit;

	for(int i=0; i< 10; i++)
	{
		_digit= _uint32/ _decimal;
		_uint32-= (_digit* _decimal);
		_decimal/= 10;

		if((0==_digit)&& (true== _leadingZero)&& (i!= 9))
		{

		}
		else
		{
			_leadingZero= false;
			DBG_DBG_PutByte(0x30+ _digit);
		}
	}
}

void DBG_Channel_Printf(DBG_Channel_t channel, const char *format, ...)
{
    char str_buf[256]; // A reasonably sized buffer for the formatted string
    va_list args;
    int len;

    // 1. Format the string with the variable arguments
    va_start(args, format);
    len = vsnprintf(str_buf, sizeof(str_buf), format, args);
    va_end(args);

    // Ensure len is not negative (error) and not larger than the buffer
    if (len < 0) {
        return; // vsnprintf error
    }
    if (len >= sizeof(str_buf)) {
        // The output was truncated, but we can still send what we have.
        // You might want to handle this case differently.
    }

    // 2. Iterate through the formatted string and put each byte into the selected channel's buffer
    for (int i = 0; i < len; i++)
    {
        switch (channel)
        {
            case CHANNEL_COM:
                DBG_COM_PutByte(str_buf[i]);
                break;
            case CHANNEL_SNF:
                DBG_SNF_PutByte(str_buf[i]);
                break;
            case CHANNEL_DBG:
                DBG_DBG_PutByte(str_buf[i]);
                break;
            // Default case is optional but good practice
            default:
                break;
        }
    }
}

#undef putchar
/*overriding gcc stdio' putchar for printf etc*/
int putchar(int c)
{
	DBG_DBG_PutByte(c);
	return c;
}

int __io_putchar(int ch)
{
	DBG_DBG_PutByte(ch);
	return ch;
}

//int fputc(int ch, FILE *f)
//{
//	DBG_DBG_PutByte(ch);
//	return 1;
//}

//int _close(int32_t file)
//{
//	return -1;
//}
//
//int _fstat(int32_t file, struct stat *st)
//{
//	return 0;
//}
//
//int _isatty(int32_t file)
//{
//	return 1;
//}
//
//int _lseek(int32_t file, int32_t ptr, int32_t dir)
//{
//	return 0;
//}

int _write(int fd, char *str, int len)
{
  for(int i= 0; i< len; i++)
  {
	  DBG_DBG_PutByte(str[i]);
  }
  return len;
}

int _read(int handle, unsigned char * buffer, size_t size)
{
	int bytes = 0;
	return bytes;
}

uint8_t __io_getcharNonBlocking(uint8_t *data)
{
    return 0;
}
