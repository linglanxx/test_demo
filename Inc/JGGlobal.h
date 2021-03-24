/**
  ******************************************************************************
  * @file    JGGlobal.h
  * @author  Laser Application Team
  * @version V1.0.0
  * @date    2-November-2015
  * @brief   This file contains the global variables of the project.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 Wanji Technology(WJ)</center></h2>
  *
  * All rights reserved.
  ******************************************************************************
  */

#ifndef __JGGLOBAL_H__
#define __JGGLOBAL_H__

#ifdef	__JGGLOBAL
#define	JGG_EXT
#else
#define	JGG_EXT	extern
#endif

#include <main.h>
#include <stdint.h>
/*---------- 全局变量定义 ----------*/

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

JGG_EXT uint16_t uart_size;//串口2接收缓存大小
JGG_EXT uint8_t uart2flag;//485有数据标志
JGG_EXT uint8_t uart485_OK;//485检测有数据
//JGG_EXT uint8_t uart485_NO;//485检测无数据

JGG_EXT uint16_t io1_unlink_cnt; //IO连续未进中断计数
JGG_EXT uint16_t io2_unlink_cnt; //IO连续未进中断计数

JGG_EXT uint8_t IO1_flag; // IO口数据标志，1为高，0为低
JGG_EXT uint8_t IO2_flag; // IO口数据标志，1为高，0为低
JGG_EXT uint8_t IO1_Int; // IO1进入过中断标志
JGG_EXT uint8_t IO2_Int; // IO2进入过中断标志


JGG_EXT uint8_t TIM_flag;


/*---------- 数据通信缓冲 ----------*/

 #define UARTBUFSIZE    2048
 #define bufsize    128
 #define BuadRate_485   115200


 JGG_EXT uint8_t UART2BUFF[UARTBUFSIZE];
 JGG_EXT uint8_t UARTBUFF[2048];


/*---------- meiju ----------*/

#endif

