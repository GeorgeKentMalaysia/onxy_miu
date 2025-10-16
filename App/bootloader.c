/**
 ******************************************************************************
 * @file           : bootloader.c
 * @brief          : Functions for bootloader
 ******************************************************************************
 * @attention
 * @PIC: muhammad.ahmad@georgekent.net
 * @Created: 1 Mar 2022
 * @Copyright: George Kent (Malaysia) Berhad.
 *
 ******************************************************************************
 **/

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "bootloader.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
 * @brief: Initialize bootloader
 * @PIC: Ricky Siah
 * @param: None
 * @retval: None
 */
static void BTLD_Init(void)
{
}

/**
 * @brief: Bootloader main loop
 * @PIC: Ricky Siah
 * @param: None
 * @retval: None
 */
void BTLD_Task(void)
{
}

/**
 * @brief: Bootloader main.
 *         Enable PARTITION = 0 for BTLD debugging
 * @PIC: Ricky Siah
 * @param: None
 * @retval: None
 */
#if PARTITION == 0
int main(void)
#else
int BTLD_Main(void)
#endif
{
    // init system
    BTLD_Init();

    // bootloader main loop
    BTLD_Task();
}