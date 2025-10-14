/**
  ******************************************************************************
  * @file           : debug.h
  * @brief          : Header for debug function
  ******************************************************************************
  * @attention
  * @PIC: muhammad.ahmad@georgekent.net
  * @Created: 18 Dec 2020
  * @Copyright: George Kent (Malaysia) Berhad.
  *
  ******************************************************************************
**/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_DBG_H_
#define INC_DBG_H_

#define DBG_CFG_BUF_SIZE		1200
#define DBG_CFG_SLEEP_DELAY_MS	1000

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>
// #include "printf.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
    DBG_STATE_RUN,   /**< The task has data to process. */
    DBG_STATE_SLEEP  /**< The task is idle and has no data to send. */
} DBG_TaskState_t;


/* Exported constants --------------------------------------------------------*/
#define DBG_CFG_BUF_SIZE 1200

/* Exported macros -----------------------------------------------------------*/
#define DBG_Print(f_, ...)  		printf((f_), ##__VA_ARGS__)
#define DBG_PrintLine(f_, ...)  	{printf((f_), ##__VA_ARGS__);printf("\r\n");}

/* Exported functions --------------------------------------------------------*/
void DBG_Init(USART_TypeDef* uart_instance);
void DBG_Task(void);

void DBG_PrintByte(uint8_t byte);

#endif /* INC_DBG_H_ */
