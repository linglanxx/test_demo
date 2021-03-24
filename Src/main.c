/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#define __JGGLOBAL
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "gui.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

//    static uint16_t unlink_cnt = 0;
//    static uint16_t io1_unlink_cnt = 0;
//    static uint16_t io2_unlink_cnt = 0;
//    static uint16_t io12_unlink_cnt = 0;
    static uint16_t uart_unlink_cnt = 0;
//    static uint16_t unlink_IO1 = 0; //一直输出低
//    static uint16_t unlink_IO2 = 0; //一直输出低
    
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  
  /* USER CODE BEGIN 2 */

    OLED_Init();				//初始化OLED
	OLED_Clear(0);             //清屏（全黑）
    
    IO1_flag = 0;
    IO2_flag = 0;
    IO1_Int = IO2_Int = 0;
    io1_unlink_cnt = io2_unlink_cnt = 0;
    uart485_OK = 0;
//    IWDG_Init(IWDG_PRESCALER_64, 1000);

    GUI_ShowString(16,0,"IO1: ",8,1);
    GUI_ShowString(72,0,"IO2: ",8,1);
    GUI_ShowString(16,10,"485 data: ",16,1);
    GUI_ShowString(16,30,"IO1 data: ",16,1);
    GUI_ShowString(16,50,"IO2 data: ",16,1);
//    MX_TIM2_Init();   // 无需开启
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//      OLED_Clear(0);
//     IWDG_Feed();
      /* IO1为高 */
      if(IO1_PIN > 0)
      {
          GUI_ShowString(48,0,"H",8,1);
      }
      else
      {
          GUI_ShowString(48,0,"L",8,1);  
      }          
      
      /* IO2为高 */
      if(IO2_PIN > 0)
      {
          GUI_ShowString(104,0,"H",8,1);

      }
      else
      {
          GUI_ShowString(104,0,"L",8,1);
      }
      
      /* 485有无数据 */
      if(uart2flag == 1)
      {
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
          HAL_Delay(1000);
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
          uart2flag = 0; 
          uart_unlink_cnt = 0;
          
      }
      // 485测到3次数据
      if(uart485_OK >= 3)
      {
          GUI_ShowString(100,10,"OK",16,1); 
      }
         
      else
      {
          GUI_ShowString(100,10,"No ",16,1);
      }
      // IO测到三次
      if(IO1_flag >= 3)
      {
          GUI_ShowString(100,30,"Yes",16,1); 
          IO1_Int = 0;
          
      }
      else
      {
          GUI_ShowString(100,30,"No ",16,1);
      }
      if(IO2_flag >= 3)
      {
          GUI_ShowString(100,50,"Yes",16,1);
          IO2_Int = 0;
      }
      else
      {
          GUI_ShowString(100,50,"No ",16,1);
      }
      
      // IO断开
      if(IO1_Int == 0) //清完中断标志后未曾进入中断
      {
          if(io1_unlink_cnt >= 25)
          {
              IO1_flag = 0;
              io1_unlink_cnt = 0;
          }  
          else
              io1_unlink_cnt++; 
      }
      if(IO2_Int == 0)
      {
          if(io2_unlink_cnt >= 25)
          {
              IO2_flag = 0;
              io2_unlink_cnt = 0;
          }  
          else
              io2_unlink_cnt++; 
      }
     
      //485断开
      if(uart2flag == 0)
      {
          if(uart_unlink_cnt > 25)
          {
              uart485_OK = 0;
              uart_unlink_cnt = 0;
          }
          else
          {
              uart_unlink_cnt++;
          }
      }
      
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
