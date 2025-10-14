/**
  ******************************************************************************
  * @file           : app_main.c
  * @brief          : Functions for main application
  ******************************************************************************
  * @attention
  * @PIC: CYK
  * @Created: 25 Sep 2025
  * @Copyright: George Kent (Malaysia) Berhad.
  * 
  ******************************************************************************
**/

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "app_main.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
  * @brief: Initialize for main application
  * @PIC: Ricky Siah
  * @param: None
  * @retval: None
  */
void APP_Init(void)
{
	DBG_Init(huart1.Instance);
	DBG_Channel_Printf(CHANNEL_DBG,"Debug module initialized!\n");
	DBG_Channel_Printf(CHANNEL_SNF,"SNF is running...\n");
	DBG_Channel_Printf(CHANNEL_SNF,"SNF is running...\n");
	DBG_Channel_Printf(CHANNEL_COM,"COM is running...\n");
	DBG_Channel_Printf(CHANNEL_COM,"COM is running...\n");
	DBG_Channel_Printf(CHANNEL_DBG,"DEBUG is running...\n");
}

/**
  * @brief: Main application
  * @PIC: Ricky Siah
  * @param: None
  * @retval: None
  */
void APP_Main(void)
{
	DBG_Task();
}
