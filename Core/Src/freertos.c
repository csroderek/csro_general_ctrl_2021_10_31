/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "fnd_input.h"
#include "fnd_output.h"
#include "fnd_com.h"
#include "fnd_eeprom.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t di_value[4];
uint8_t id_value[8];
uint8_t do_value[6];
float adc_value[10];
float sht_value[4];
uint16_t speed_value[2];
uint16_t step_value[4];
uint16_t pwm_value[3];

uint16_t eeprom_test_value = 0;

/* USER CODE END Variables */
/* Definitions for myTask01 */
osThreadId_t myTask01Handle;
const osThreadAttr_t myTask01_attributes = {
  .name = "myTask01",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh3,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh1,
};
/* Definitions for myTask05 */
osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "myTask05",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal7,
};
/* Definitions for myTask06 */
osThreadId_t myTask06Handle;
const osThreadAttr_t myTask06_attributes = {
  .name = "myTask06",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal5,
};
/* Definitions for myTask07 */
osThreadId_t myTask07Handle;
const osThreadAttr_t myTask07_attributes = {
  .name = "myTask07",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal3,
};
/* Definitions for myTask08 */
osThreadId_t myTask08Handle;
const osThreadAttr_t myTask08_attributes = {
  .name = "myTask08",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};
/* Definitions for myTask09 */
osThreadId_t myTask09Handle;
const osThreadAttr_t myTask09_attributes = {
  .name = "myTask09",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask01(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);
void StartTask06(void *argument);
void StartTask07(void *argument);
void StartTask08(void *argument);
void StartTask09(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  fnd_com_modbus_rtu_init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of myTask01 */
  myTask01Handle = osThreadNew(StartTask01, NULL, &myTask01_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* creation of myTask05 */
  myTask05Handle = osThreadNew(StartTask05, NULL, &myTask05_attributes);

  /* creation of myTask06 */
  myTask06Handle = osThreadNew(StartTask06, NULL, &myTask06_attributes);

  /* creation of myTask07 */
  myTask07Handle = osThreadNew(StartTask07, NULL, &myTask07_attributes);

  /* creation of myTask08 */
  myTask08Handle = osThreadNew(StartTask08, NULL, &myTask08_attributes);

  /* creation of myTask09 */
  myTask09Handle = osThreadNew(StartTask09, NULL, &myTask09_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTask01 */
/**
 * @brief  Function implementing the myTask01 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask01 */
void StartTask01(void *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartTask01 */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartTask01 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the myTask02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for (;;)
  {
    fnd_com_modbus_rtu_slave1_wait();
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the myTask03 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for (;;)
  {
    fnd_com_modbus_rtu_slave2_wait();
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
 * @brief Function implementing the myTask04 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for (;;)
  {
    fnd_com_modbus_rtu_slave3_wait();
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
 * @brief Function implementing the myTask05 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for (;;)
  {
    fnd_com_modbus_rtu_slave4_wait();
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
 * @brief Function implementing the myTask06 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask06 */
void StartTask06(void *argument)
{
  /* USER CODE BEGIN StartTask06 */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask06 */
}

/* USER CODE BEGIN Header_StartTask07 */
/**
 * @brief Function implementing the myTask07 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask07 */
void StartTask07(void *argument)
{
  /* USER CODE BEGIN StartTask07 */
  /* Infinite loop */
  for (;;)
  {
    osDelay(10);
    fnd_output_stepper_10ms_tick();
  }
  /* USER CODE END StartTask07 */
}

/* USER CODE BEGIN Header_StartTask08 */
/**
 * @brief Function implementing the myTask08 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask08 */
void StartTask08(void *argument)
{
  /* USER CODE BEGIN StartTask08 */

  /* Infinite loop */
  for (;;)
  {
    osDelay(100);
    fnd_input_gpio_read_di(di_value);
    fnd_input_gpio_read_id(id_value);

    fnd_input_adc_read_dp(&adc_value[0]);
    fnd_input_adc_read_ntc(&adc_value[3]);
    fnd_input_adc_read_val_fb(&adc_value[9]);

    fnd_input_i2c_read_sht(sht_value);

    fnd_input_tim_input_read_speed(speed_value);

    fnd_output_gpio_write_do(do_value);
    fnd_output_pwm_write_value(pwm_value);
    fnd_output_stepper_set_position(step_value);
  }
  /* USER CODE END StartTask08 */
}

/* USER CODE BEGIN Header_StartTask09 */
/**
 * @brief Function implementing the myTask09 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask09 */
void StartTask09(void *argument)
{
  /* USER CODE BEGIN StartTask09 */
  /* Infinite loop */
  for (;;)
  {
    osDelay(200);
    HAL_GPIO_TogglePin(LED_01_GPIO_Port, LED_01_Pin);
  }
  /* USER CODE END StartTask09 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
