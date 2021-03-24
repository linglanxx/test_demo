/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */
//--------------SPI总线引脚定义-----------------------
#define OLED_MOSI      GPIO_PIN_7//GPIO_Pin_5  //OLED屏SPI写数据信号
#define OLED_CLK       GPIO_PIN_5//GPIO_Pin_3  //OLED屏SPI时钟信号

//--------------SPI端口操作定义---------------------
#define	OLED_MOSI_SET()  	HAL_GPIO_WritePin(GPIOA, OLED_MOSI, GPIO_PIN_SET)//GPIO_SetBits(GPIOB,OLED_MOSI) 
#define	OLED_MOSI_CLR()  	HAL_GPIO_WritePin(GPIOA, OLED_MOSI, GPIO_PIN_RESET)//GPIO_ResetBits(GPIOB,OLED_MOSI) 
  
#define	OLED_CLK_SET()  	HAL_GPIO_WritePin(GPIOA, OLED_CLK, GPIO_PIN_SET)//GPIO_SetBits(GPIOB,OLED_CLK)    
#define	OLED_CLK_CLR()  	HAL_GPIO_WritePin(GPIOA, OLED_CLK, GPIO_PIN_RESET)//GPIO_ResetBits(GPIOB,OLED_CLK)
/* USER CODE END Private defines */

void MX_SPI1_Init(void);

/* USER CODE BEGIN Prototypes */
u8 SPI2_ReadWriteByte(u8 TxData);
//u8 SPI2_ReadWriteByte(u8 TxData);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
