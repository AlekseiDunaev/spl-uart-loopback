/**
  ******************************************************************************
  * @file    UART1_Interrupt\main.h
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   This file contains the external declaration of main.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s_conf.h"
#include "string.h"
#include "delay.h"
/* Private variables ---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
// #define TxBufferSize   (countof(TxBuffer) - 1)
// #define RxBufferSize   TxBufferSize
#define RxBufferSize   256
#define LED_PORT  GPIOE
#define LED_PIN   GPIO_PIN_5

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
// #define LED_ON    (LED_PORT->ODR |= LED_PIN)
#define LED_ON    GPIO_WriteLow(LED_PORT, LED_PIN)
// #define LED_OFF   (LED_PORT->ODR &= (u8)(~LED_PIN))
#define LED_OFF    GPIO_WriteHigh(LED_PORT, LED_PIN)
// #define LED_STATE (LED_PORT->IDR & LED_PIN)

/* Exported functions ------------------------------------------------------- */
uint8_t GetVar_TxCounter(void);
uint8_t IncrementVar_TxCounter(void);
uint8_t GetVar_RxCounter(void);
uint8_t IncrementVar_RxCounter(void);
void ResetVar_RxCounter(void);
TestStatus GetVar_TestStatus(void);
void SetVar_TestStatus(void);
void ResetVar_TestStatus(void);
void SendString(char *str, uint8_t size);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
