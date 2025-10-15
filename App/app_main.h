/**
  ******************************************************************************
  * @file           : app_main.c
  * @brief          : Functions for main application
  ******************************************************************************
  * @attention
  * @PIC: CYK
  * @Authors:
  *   15 Oct 2025	yee-kong.chong@georgekent.net – Original version
  *
  * @Copyright: George Kent (Malaysia) Berhad.
  *
  ******************************************************************************
**/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_MAIN_H
#define APP_MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "dbg.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void APP_Init(void);
void APP_Main(void);

#endif /* APP_MAIN_H */ 
