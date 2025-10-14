/**
  ******************************************************************************
  * @file           : dbg.c
  * @brief          : Functions for debug task
  ******************************************************************************
  * @attention
  * @PIC: muhammad.ahmad@georgekent.net
  * @Created: 18 Dec 2020
  * @Copyright: George Kent (Malaysia) Berhad.
  * 
  ******************************************************************************
**/

/* Private includes ----------------------------------------------------------*/
#include "dbg.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define CHANNEL_MARKER_LEN (sizeof(pcChannelMarker) - 1)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// Pointer to the UART peripheral instance, provided by the user.
static USART_TypeDef* dbg_uart = NULL;

// Double buffer for debug messages. Channel 0 is for printf, Channel 1 is for raw bytes.
static uint8_t  pucDbgBuf[2][DBG_CFG_BUF_SIZE];
static volatile uint16_t ucDbgHead[2] = {0, 0};
static volatile uint16_t ucDbgTail[2] = {0, 0};

// Channel marker to identify the source of the debug output.
static char pcChannelMarker[] = "  <dbg#0>";

// State variables for the transmission task.
static char* cChannel;
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

    // Initialize buffer pointers.
    for (int i = 0; i < 2; i++) {
        ucDbgHead[i] = 0;
        ucDbgTail[i] = 0;
    }

    // Initialize channel marker state.
    // The marker is "<dbg#X>" where X is the channel index (0 or 1).
    cChannel = pcChannelMarker + 7; // Points to the '0'
    cChannelInd = 0;

    // Ensure UART is enabled. This is a safe check.
    // The peripheral should already be configured and enabled by the application.
    if ((dbg_uart->CR1 & USART_CR1_UE) == 0)
    {
        LL_USART_Enable(dbg_uart);
    }
}

void DBG_Task(void)
{
    bool data_to_send = false;
    uint8_t data_byte = 0;

    // Check if the module has been initialized.
    if (dbg_uart == NULL) {
        return;
    }

    // Proceed only if the transmit complete flag is set, meaning the peripheral is ready.
    if (LL_USART_IsActiveFlag_TC(dbg_uart))
    {
        // First, send the channel marker if it hasn't been fully sent.
        if (cChannelInd < CHANNEL_MARKER_LEN)
        {
            data_byte = pcChannelMarker[cChannelInd++];
            data_to_send = true;
        }
        else
        {
            // Channel marker sent, now process the data buffers.
            switch(*cChannel)
            {
                case '0': // Process channel 0 (printf buffer)
                    if (ucDbgHead[0] != ucDbgTail[0])
                    {
                        data_byte = pucDbgBuf[0][(ucDbgHead[0]++) % DBG_CFG_BUF_SIZE];
                        data_to_send = true;
                    }
                    else if (ucDbgHead[1] != ucDbgTail[1]) // Channel 0 empty, switch to 1
                    {
                        *cChannel = '1';
                        cChannelInd = 0; // Reset to send marker for the new channel
                    }
                    break;

                case '1': // Process channel 1 (byte buffer)
                    if (ucDbgHead[1] != ucDbgTail[1])
                    {
                        data_byte = pucDbgBuf[1][(ucDbgHead[1]++) % DBG_CFG_BUF_SIZE];
                        data_to_send = true;
                    }
                    else if (ucDbgHead[0] != ucDbgTail[0]) // Channel 1 empty, switch to 0
                    {
                        *cChannel = '0';
                        cChannelInd = 0; // Reset to send marker for the new channel
                    }
                    break;
            }
        }

        if (data_to_send)
        {
            LL_USART_TransmitData8(dbg_uart, data_byte);
        }
    }
}

DBG_TaskState_t DBG_GetTaskState(void)
{
    // The task is busy if the UART is not ready for transmission,
    // or if the channel marker is not fully sent,
    // or if either of the buffers contains data.
    bool is_busy = (LL_USART_IsActiveFlag_TC(dbg_uart) == 0) ||
                   (cChannelInd < CHANNEL_MARKER_LEN) ||
                   (ucDbgHead[0] != ucDbgTail[0]) ||
                   (ucDbgHead[1] != ucDbgTail[1]);

    return is_busy ? DBG_STATE_RUN : DBG_STATE_SLEEP;
}

void DBG_PrintByte(uint8_t byte)
{
    // Add a byte to the secondary buffer (channel 1).
    // This is a circular buffer; the head/tail pointers will wrap naturally.
    pucDbgBuf[1][(ucDbgTail[1]++) % DBG_CFG_BUF_SIZE] = byte;
}

/**
 * @brief This function is the required hook for the printf library.
 * It redirects the output of printf into the debug module's buffer (channel 0).
 * @param character The character to be printed.
 */
void _putchar(char character)
{
    // Add character from printf to the primary buffer (channel 0).
    pucDbgBuf[0][(ucDbgTail[0]++) % DBG_CFG_BUF_SIZE] = (uint8_t)character;
}
