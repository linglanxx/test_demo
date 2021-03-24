/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
#include "gpio.h"
#include "stdlib.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable Interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
    
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);

  /* USER CODE END EXTI4_15_IRQn 0 */
//    if(TIM_flag == 0)
//    {
//        HAL_TIM_Base_Start_IT(&htim2); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE
//        TIM_flag = 1;
//    }
    /* 判断那个IO此时为高 */
//    if(IO1_PIN == 1)
//    {
//        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
//    }
//    else
//    {
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
//    }
//    if(IO2_PIN == 1)
//    {
//        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
//    }
//    else
//    {
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
//    }
  
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */
    

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 4, channel 5, channel 6 and channel 7 interrupts.
  */
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 0 */

  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 1 */

  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
    uint32_t tem = 0;
    tem = __HAL_UART_GET_FLAG(&huart2,UART_IT_IDLE);
    if(tem == RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart2);
        HAL_UART_DMAStop(&huart2);    //HAL_UART_AbortReceive()
        uart_size = UARTBUFSIZE - hdma_usart2_rx.Instance->CNDTR; //数组长度-剩余接收=实际长度
        
        /*485传输的数据为： 0xFF 0xAA 0x02 0x03 0x04 0xff buadrate_485>>24&0xff  buadrate_485>>16&0xff buadrate_485>>8&0xff buadrate_485>>0&0xff 0x05 0xEE 0xEE */
        /* 判断接收到的485数据  判断FF AA 和波特率 115200 分四字节存放*/
        if(UART2BUFF[0] == 0xff&&UART2BUFF[1] == 0xaa&&UART2BUFF[6] == 0x00&&UART2BUFF[7] == 0x01
            &&UART2BUFF[8] == 0xc2&&UART2BUFF[9] == 0x00)
         {
            uart2flag = 1;
            memcpy(UARTBUFF,UART2BUFF,uart_size);
            memset(UART2BUFF,0,sizeof(UART2BUFF));
            if(uart485_OK > 10)
                uart485_OK = 3;
            else 
                uart485_OK++;
         }
         
         else
         {
             uart2flag = 0;
         }
       HAL_UART_Receive_DMA(&huart2,UART2BUFF,UARTBUFSIZE);
    }
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}
static uint32_t tick1_up[3] = {0}, tick1 = 0, tick2_up[3] = {0}, tick2 = 0;

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(INTPUT_CTL1_Pin == GPIO_Pin)
    {
        IO1_Int = 1;
        io1_unlink_cnt = 0;
        tick1_up[1] = HAL_GetTick();
        if(tick1_up[1] > tick1_up[0])
        {
            tick1 = tick1_up[1] - tick1_up[0];
            tick1_up[0] = tick1_up[1];
            if(tick1 >= 4000)
            {
                if(tick1 - 4000 < 50)
                    IO1_flag++; 
                    
            }
            else
            {
                if(4000 - tick1 < 50)
                    IO1_flag++;
            }
                
        }
  
    }
    if(IO1_flag >= 10)
        IO1_flag = 3;
    if(INTPUT_CTL2_Pin == GPIO_Pin)
    {
        IO2_Int = 1;
        io2_unlink_cnt = 0;
        tick2_up[1] = HAL_GetTick();
        if(tick2_up[1] > tick2_up[0])
        {
            tick2 = tick2_up[1] - tick2_up[0];
            tick2_up[0] = tick2_up[1];
            if(tick2 >= 4000)
            {
                if(tick2 - 4000 < 50)
                    IO2_flag++;   
                    
            }
            else
            {
                if(4000 - tick2 < 50)
                    IO2_flag++;
            }
                
        }
  
    }
    if(IO2_flag >= 10)
        IO2_flag = 3;
    
//    /* 记录上升沿次数 */
//    if(GPIO_Pin == INTPUT_CTL1_Pin)
//    {
//        IO1_time++;
//    }
//    
//    if(GPIO_Pin == INTPUT_CTL2_Pin)
//    {
//        IO2_time++;
//    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* 超过2个上升沿即认定有数据 */
//    if(htim==(&htim2))
//    {
//        if(IO1_time >= 3)
//        {
//            IO1_OK = 1;
////            IO1_time = 0;
//    //        HAL_TIM_Base_Stop_IT(&htim2);
//        }
////        else IO1_OK = 0;
//        
//        if(IO2_time >= 3)
//        {
//            IO2_OK = 1;
////            IO2_time = 0;
//    //        HAL_TIM_Base_Stop_IT(&htim2);
//        }
////        else IO2_OK = 0;
//    }
    
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
