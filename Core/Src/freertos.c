/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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


#include "AngleGetTask.h"

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
osThreadId defaultTaskHandle;
osThreadId SendDataTaskHandle;
osThreadId IMU_TaskHandle;
osThreadId AngleGetTeskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartSendDataTask(void const * argument);
void Start_IMU_Task(void const * argument);
void StartAngleGetTesk(void const * argument);

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
  /* definition and creation of defaultTask */
  // osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 64);
  // defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of SendDataTask */
  osThreadDef(SendDataTask, StartSendDataTask, osPriorityNormal, 0, 128);
  SendDataTaskHandle = osThreadCreate(osThread(SendDataTask), NULL);

  /* definition and creation of IMU_Task */
  // osThreadDef(IMU_Task, Start_IMU_Task, osPriorityIdle, 0, 128);
  // IMU_TaskHandle = osThreadCreate(osThread(IMU_Task), NULL);

  /* definition and creation of AngleGetTesk */
//  osThreadDef(AngleGetTesk, StartAngleGetTesk, osPriorityNormal, 0, 128);
//  AngleGetTeskHandle = osThreadCreate(osThread(AngleGetTesk), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadDef(AngleGetTesk, Angle_Get_Task, osPriorityHigh, 0, 128);
  AngleGetTeskHandle = osThreadCreate(osThread(AngleGetTesk), NULL);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSendDataTask */
/**
* @brief Function implementing the SendDataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendDataTask */
__weak void StartSendDataTask(void const * argument)
{
  /* USER CODE BEGIN StartSendDataTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSendDataTask */
}

/* USER CODE BEGIN Header_Start_IMU_Task */
/**
* @brief Function implementing the IMU_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_IMU_Task */
__weak void Start_IMU_Task(void const * argument)
{
  /* USER CODE BEGIN Start_IMU_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_IMU_Task */
}

/* USER CODE BEGIN Header_StartAngleGetTesk */
/**
* @brief Function implementing the AngleGetTesk thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAngleGetTesk */
__weak void StartAngleGetTesk(void const * argument)
{
  /* USER CODE BEGIN StartAngleGetTesk */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartAngleGetTesk */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
