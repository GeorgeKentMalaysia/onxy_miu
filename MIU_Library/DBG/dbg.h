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
// #include "printf.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
#define DBG_Print(f_, ...)  		printf((f_), ##__VA_ARGS__)
#define DBG_PrintLine(f_, ...)  	{printf((f_), ##__VA_ARGS__);printf("\r\n");}

/* Exported functions --------------------------------------------------------*/
void DBG_Init(void);
void DBG_Task(void);

#endif /* INC_DBG_H_ */
