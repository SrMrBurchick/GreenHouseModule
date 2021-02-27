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
#include "green_house.h"
#include "logger_api.h"
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

/* USER CODE END Variables */
osThreadId heartBeatHandle;
uint32_t heartBeatBuffer[ 128 ];
osStaticThreadDef_t heartBeatControlBlock;
osThreadId consoleHandle;
uint32_t consoleBuffer[ 128 ];
osStaticThreadDef_t consoleControlBlock;
osThreadId sensorMonitorHandle;
uint32_t sensorMonitorBuffer[ 128 ];
osStaticThreadDef_t sensorMonitorControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void heartBeatTask(void const * argument);
void consoleTask(void const * argument);
void sensorMonitorTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

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
  /* definition and creation of heartBeat */
  osThreadStaticDef(heartBeat, heartBeatTask, osPriorityNormal, 0, 128, heartBeatBuffer, &heartBeatControlBlock);
  heartBeatHandle = osThreadCreate(osThread(heartBeat), NULL);

  /* definition and creation of console */
  osThreadStaticDef(console, consoleTask, osPriorityIdle, 0, 128, consoleBuffer, &consoleControlBlock);
  consoleHandle = osThreadCreate(osThread(console), NULL);

  /* definition and creation of sensorMonitor */
  osThreadStaticDef(sensorMonitor, sensorMonitorTask, osPriorityIdle, 0, 128, sensorMonitorBuffer, &sensorMonitorControlBlock);
  sensorMonitorHandle = osThreadCreate(osThread(sensorMonitor), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_heartBeatTask */
/**
  * @brief  Function implementing the heartBeat thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_heartBeatTask */
void heartBeatTask(void const * argument)
{
  /* USER CODE BEGIN heartBeatTask */
  /* Infinite loop */
    start_app();
  for(;;)
  {
      HAL_GPIO_TogglePin(HEARTBEAT_LED_GPIO_Port, HEARTBEAT_LED_Pin);
    osDelay(500);
  }
  /* USER CODE END heartBeatTask */
}

/* USER CODE BEGIN Header_consoleTask */
/**
* @brief Function implementing the console thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_consoleTask */
void consoleTask(void const * argument)
{
  /* USER CODE BEGIN consoleTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END consoleTask */
}

/* USER CODE BEGIN Header_sensorMonitorTask */
/**
* @brief Function implementing the sensorMonitor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sensorMonitorTask */
void sensorMonitorTask(void const * argument)
{
  /* USER CODE BEGIN sensorMonitorTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END sensorMonitorTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
