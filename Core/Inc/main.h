/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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
#define RLY_05_Pin GPIO_PIN_2
#define RLY_05_GPIO_Port GPIOE
#define RLY_06_Pin GPIO_PIN_3
#define RLY_06_GPIO_Port GPIOE
#define ID_DATA_Pin GPIO_PIN_4
#define ID_DATA_GPIO_Port GPIOE
#define ID_LD_Pin GPIO_PIN_5
#define ID_LD_GPIO_Port GPIOE
#define ID_CLK_Pin GPIO_PIN_6
#define ID_CLK_GPIO_Port GPIOE
#define STEP_B8_Pin GPIO_PIN_13
#define STEP_B8_GPIO_Port GPIOC
#define STEP_B7_Pin GPIO_PIN_14
#define STEP_B7_GPIO_Port GPIOC
#define STEP_B6_Pin GPIO_PIN_15
#define STEP_B6_GPIO_Port GPIOC
#define NTC_01_Pin GPIO_PIN_0
#define NTC_01_GPIO_Port GPIOC
#define NTC_02_Pin GPIO_PIN_2
#define NTC_02_GPIO_Port GPIOC
#define NTC_03_Pin GPIO_PIN_3
#define NTC_03_GPIO_Port GPIOC
#define NTC_04_Pin GPIO_PIN_0
#define NTC_04_GPIO_Port GPIOA
#define NTC_05_Pin GPIO_PIN_3
#define NTC_05_GPIO_Port GPIOA
#define NTC_06_Pin GPIO_PIN_4
#define NTC_06_GPIO_Port GPIOA
#define DP_01_Pin GPIO_PIN_5
#define DP_01_GPIO_Port GPIOA
#define DP_02_Pin GPIO_PIN_6
#define DP_02_GPIO_Port GPIOA
#define DP_03_Pin GPIO_PIN_0
#define DP_03_GPIO_Port GPIOB
#define VAL_FB_Pin GPIO_PIN_1
#define VAL_FB_GPIO_Port GPIOB
#define STEP_B5_Pin GPIO_PIN_2
#define STEP_B5_GPIO_Port GPIOB
#define STEP_B4_Pin GPIO_PIN_7
#define STEP_B4_GPIO_Port GPIOE
#define STEP_B3_Pin GPIO_PIN_8
#define STEP_B3_GPIO_Port GPIOE
#define FAN1_PWM_Pin GPIO_PIN_9
#define FAN1_PWM_GPIO_Port GPIOE
#define STEP_B2_Pin GPIO_PIN_10
#define STEP_B2_GPIO_Port GPIOE
#define FAN2_PWM_Pin GPIO_PIN_11
#define FAN2_PWM_GPIO_Port GPIOE
#define STEP_B1_Pin GPIO_PIN_12
#define STEP_B1_GPIO_Port GPIOE
#define STEP_A8_Pin GPIO_PIN_13
#define STEP_A8_GPIO_Port GPIOE
#define STEP_A7_Pin GPIO_PIN_14
#define STEP_A7_GPIO_Port GPIOE
#define STEP_A6_Pin GPIO_PIN_15
#define STEP_A6_GPIO_Port GPIOE
#define ETH_RSTN_Pin GPIO_PIN_10
#define ETH_RSTN_GPIO_Port GPIOB
#define STEP_A5_Pin GPIO_PIN_14
#define STEP_A5_GPIO_Port GPIOB
#define RS485_EN3_Pin GPIO_PIN_15
#define RS485_EN3_GPIO_Port GPIOB
#define STEP_A4_Pin GPIO_PIN_10
#define STEP_A4_GPIO_Port GPIOD
#define STEP_A3_Pin GPIO_PIN_11
#define STEP_A3_GPIO_Port GPIOD
#define STEP_A2_Pin GPIO_PIN_12
#define STEP_A2_GPIO_Port GPIOD
#define STEP_A1_Pin GPIO_PIN_13
#define STEP_A1_GPIO_Port GPIOD
#define RS485_EN4_Pin GPIO_PIN_15
#define RS485_EN4_GPIO_Port GPIOD
#define LED_01_Pin GPIO_PIN_8
#define LED_01_GPIO_Port GPIOC
#define TH_SDA2_Pin GPIO_PIN_9
#define TH_SDA2_GPIO_Port GPIOC
#define TH_SCL2_Pin GPIO_PIN_8
#define TH_SCL2_GPIO_Port GPIOA
#define RS485_EN1_Pin GPIO_PIN_11
#define RS485_EN1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define DS1302_CLK_Pin GPIO_PIN_10
#define DS1302_CLK_GPIO_Port GPIOC
#define DS1302_IO_Pin GPIO_PIN_11
#define DS1302_IO_GPIO_Port GPIOC
#define DS1302_RST_Pin GPIO_PIN_12
#define DS1302_RST_GPIO_Port GPIOC
#define DI_04_Pin GPIO_PIN_0
#define DI_04_GPIO_Port GPIOD
#define DI_03_Pin GPIO_PIN_1
#define DI_03_GPIO_Port GPIOD
#define DI_02_Pin GPIO_PIN_2
#define DI_02_GPIO_Port GPIOD
#define DI_01_Pin GPIO_PIN_3
#define DI_01_GPIO_Port GPIOD
#define RS485_EN2_Pin GPIO_PIN_4
#define RS485_EN2_GPIO_Port GPIOD
#define VAL_PWM_Pin GPIO_PIN_3
#define VAL_PWM_GPIO_Port GPIOB
#define FAN1_SPD_Pin GPIO_PIN_4
#define FAN1_SPD_GPIO_Port GPIOB
#define FAN2_SPD_Pin GPIO_PIN_5
#define FAN2_SPD_GPIO_Port GPIOB
#define TH_SCL1_Pin GPIO_PIN_6
#define TH_SCL1_GPIO_Port GPIOB
#define TH_SDA1_Pin GPIO_PIN_7
#define TH_SDA1_GPIO_Port GPIOB
#define RLY_01_Pin GPIO_PIN_8
#define RLY_01_GPIO_Port GPIOB
#define RLY_02_Pin GPIO_PIN_9
#define RLY_02_GPIO_Port GPIOB
#define RLY_03_Pin GPIO_PIN_0
#define RLY_03_GPIO_Port GPIOE
#define RLY_04_Pin GPIO_PIN_1
#define RLY_04_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
