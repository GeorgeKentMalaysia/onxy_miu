/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

#include "stm32l4xx_ll_crs.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NB_PSM_EINT_Pin GPIO_PIN_13
#define NB_PSM_EINT_GPIO_Port GPIOC
#define MEMS_INT2_Pin GPIO_PIN_0
#define MEMS_INT2_GPIO_Port GPIOH
#define MEMS_INT1_Pin GPIO_PIN_1
#define MEMS_INT1_GPIO_Port GPIOH
#define VBATT_ADC_Pin GPIO_PIN_0
#define VBATT_ADC_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_1
#define SPI1_SCK_GPIO_Port GPIOA
#define NFC_BUSY_Pin GPIO_PIN_2
#define NFC_BUSY_GPIO_Port GPIOA
#define COMP2_INP_CH1_Pin GPIO_PIN_3
#define COMP2_INP_CH1_GPIO_Port GPIOA
#define TAMPER_IN_Pin GPIO_PIN_5
#define TAMPER_IN_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_0
#define SPI1_NSS_GPIO_Port GPIOB
#define NB_PWR_BYPASS_Pin GPIO_PIN_1
#define NB_PWR_BYPASS_GPIO_Port GPIOB
#define NB_PWR_EN_Pin GPIO_PIN_2
#define NB_PWR_EN_GPIO_Port GPIOB
#define LPUART1_RX_Pin GPIO_PIN_10
#define LPUART1_RX_GPIO_Port GPIOB
#define LPUART1_TX_Pin GPIO_PIN_11
#define LPUART1_TX_GPIO_Port GPIOB
#define SIM_DT_Pin GPIO_PIN_12
#define SIM_DT_GPIO_Port GPIOB
#define I2C2SCL_Pin GPIO_PIN_13
#define I2C2SCL_GPIO_Port GPIOB
#define I2C2_SDA_Pin GPIO_PIN_14
#define I2C2_SDA_GPIO_Port GPIOB
#define FUEL_GAUGE_ALRT_Pin GPIO_PIN_15
#define FUEL_GAUGE_ALRT_GPIO_Port GPIOB
#define VBATT_DET_Pin GPIO_PIN_8
#define VBATT_DET_GPIO_Port GPIOA
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define PWR_BY_MAG_Pin GPIO_PIN_11
#define PWR_BY_MAG_GPIO_Port GPIOA
#define NFC_PWR_Pin GPIO_PIN_12
#define NFC_PWR_GPIO_Port GPIOA
#define NB_ONOFF_Pin GPIO_PIN_15
#define NB_ONOFF_GPIO_Port GPIOA
#define PWR_EN_Pin GPIO_PIN_6
#define PWR_EN_GPIO_Port GPIOB
#define NB_RESET_Pin GPIO_PIN_3
#define NB_RESET_GPIO_Port GPIOH
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
