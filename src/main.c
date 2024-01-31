/**
  ******************************************************************************
  * @file UART1_Interrupt\main.c
  * @brief This file contains the main function for a basic communication between UART1 and UART3 using interrupts.
  * @author  MCD Application Team
  * @version V2.0.4
  * @date     26-April-2018
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

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */
#include "main.h"

/**
  * @addtogroup UART1_Interrupt
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// uint8_t TxBuffer[] = "UART2 Interrupt Example";
uint8_t RxBuffer[RxBufferSize];
// uint8_t RxBuffer[RxBufferSize] = "Test UART2 transmite reseive\n";
// __IO uint8_t TxCounter = 0x00;
__IO uint8_t RxCounter = 0x00;
__IO TestStatus TransferStatus = FAILED;

/* Private function prototypes -----------------------------------------------*/
// TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void CLK_Config(void);
static void UART_Config(void);
static void GPIO_Config(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* CLK configuration -----------------------------------------*/
  CLK_Config();

  /* UART configuration -----------------------------------------*/
  UART_Config();  
  
  /* GPIO configuration -----------------------------------------*/
  GPIO_Config();

  // UART2_ITConfig(UART2_IT_TXE, ENABLE);
  // while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);
  // while(UART2_GetITStatus(UART2_IT_TC) != RESET);
  // memset(RxBuffer, '\0', RxBufferSize);
  
  while (1)
  {
  }
}

/**
  * @brief  Configure system clock to run at 16Mhz
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
  /* Initialization of the clock */
  /* Clock divider to HSI/1 */
  CLK_DeInit();
  CLK_HSECmd(DISABLE);
  CLK_LSICmd(DISABLE);
  CLK_HSICmd(ENABLE);
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);
  CLK_ClockSwitchCmd(ENABLE);
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
}

/**
  * @brief  UART1 and UART3 Configuration for interrupt communication
  * @param  None
  * @retval None
  */
static void UART_Config(void)
{
  /* Deinitializes the UART1 and UART3 peripheral */
    // UART1_DeInit();
    // UART3_DeInit();
    UART2_DeInit();
    /* UART1 and UART3 configuration -------------------------------------------------*/
    /* UART1 and UART3 configured as follow:
          - BaudRate = 9600 baud  
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Receive and transmit enabled
          - UART1 Clock disabled
     */
    /* Configure the UART1 */
    // UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
    //            UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    
    /* Enable UART1 Transmit interrupt*/
    // UART1_ITConfig(UART1_IT_TXE, ENABLE);
    
    /* Configure the UART3 */
 		// UART3_Init((uint32_t)9600, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, UART3_PARITY_NO,
    //            UART3_MODE_TXRX_ENABLE);

    /* Enable UART3 Receive interrupt */
     
    /* UART2 configured as follow:
      - BaudRate = 9600 baud  
      - Word Length = 8 Bits
      - One Stop Bit
      - No parity
      - Receive and transmit enabled
      - UART1 Clock disabled
    */

    /* Configure the UART2 */
 		UART2_Init((uint32_t)9600, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, \
      UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);

    /* Enable UART2 Receive interrupt */
    UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);
    // UART2_ITConfig(UART2_IT_IDLE, ENABLE);

    UART2_Cmd(ENABLE);
    
    /* Enable general interrupts */
    enableInterrupts();    
}

static void GPIO_Config(void) {
  // GPIO_DeInit(GPIOA);
  // GPIO_DeInit(GPIOB);
  // GPIO_DeInit(GPIOC);
  // GPIO_DeInit(GPIOD);
  GPIO_DeInit(GPIOE);
  GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

/**
  * @brief Returns TxCounter1 value.
  * @param None
  * @retval Transmit counter index1
  * - uint8_t: TxCounter1
  * @par Required preconditions:
  * None
  */
/*
uint8_t GetVar_TxCounter(void)
{
return TxCounter;
}
*/

/**
  * @brief Returns RxCounter1 value.
  * @param None
  * @retval Receive counter index1
  * - uint8_t: RxCounter1
  * @par Required preconditions:
  * None
  */
uint8_t GetVar_RxCounter(void)
{
return RxCounter;
}

void ResetVar_RxCounter(void)
{
  RxCounter = 0;
}

TestStatus GetVar_TestStatus(void)
{
  return TransferStatus;
}

void SetVar_TestStatus(void)
{
  TransferStatus = PASSED;
}

void ResetVar_TestStatus(void)
{
  TransferStatus = FAILED;
}

/**
  * @brief Increments TxCounter1 variable and return its value 
  * @param None
  * @retval Transmit counter index1++
  * - uint8_t: TxCounter1++
  * @par Required preconditions:
  * None
  */
/*
uint8_t IncrementVar_TxCounter(void)
{
	return TxCounter++;
}
*/

/**
  * @brief Increments RxCounter1 variable and return its value 
  * @param None
  * @retval Receive counter index1++
  * - uint8_t: RxCounter1++
  * @par Required preconditions:
  * None
  */
uint8_t IncrementVar_RxCounter(void)
{
	return RxCounter++;
}

void SendString(char *str, uint8_t size)
{
  for (uint8_t i = 0; i < size; i++)
    UART2_SendData8(str[i]);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  (void) file;
  (void) line;
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
