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

/* Private includes ----------------------------------------------------------*/
#include "app_main.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

void APP_Init(void)
{
    DBG_Init(huart1.Instance);
    DBG_Channel_Printf(CHANNEL_DBG,"Debug module initialized!\n");
    DBG_Channel_Printf(CHANNEL_SNF,"From SNF\n");
    DBG_Channel_Printf(CHANNEL_COM,"From COM\n");
}


void APP_Main(void)
{
	DBG_Task();
}
