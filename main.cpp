/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "InstantRodos.h"
#include "IdleTask.h"
#include "ThreadWithTimer.h"

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"


/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

//TIM_TimeBaseInitTypeDef    TIM_InitStruct; 
TIM_TimeBaseInitTypeDef    SetupTimer; 

void configureTheTimer() 
{

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//TIM_InitStruct.TIM_Prescaler = 42000 - 1;                // This will configure the clock to 2 kHz
//TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;     // Count-up timer mode
//TIM_InitStruct.TIM_Period = 0xffffffff - 1;                    // 2 kHz down to 1 Hz = 1 second
//TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        // Divide clock by 1
//TIM_InitStruct.TIM_RepetitionCounter = 0;                // Set to 0, not used
//TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
/* TIM2 enable counter */

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
SetupTimer.TIM_Prescaler = 0xFFFF;
SetupTimer.TIM_CounterMode = TIM_CounterMode_Up;
SetupTimer.TIM_Period = 0xFFFFFFFF;
SetupTimer.TIM_ClockDivision = TIM_CKD_DIV4;
TIM_TimeBaseInit(TIM2, &SetupTimer);
TIM_Cmd(TIM2, ENABLE);


}




void USART_Config(void)
{
    // Enable clock for GPIOD
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    // Enable clock for USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // Connect PD8 to USART3_Tx
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
    // Connect PD9 to USART3_Rx
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
    
    

    // Initialization of GPIOd	
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    // Initialization of USART3
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl =
            USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStruct);

    // Enable USART3
    USART_Cmd(USART3, ENABLE);
}



void doBlinks() 
{
    /* PD12 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
    
    /* Insert delay */
    Delay(0x3FFFFF);
    
    /* PD13 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_13);
    
    /* Insert delay */
    
    Delay(0x3FFFFF);
    Delay(0x3FFFFF);
  
    /* PD14 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    Delay(0x3FFFFF);
    Delay(0x3FFFFF);
  
    /* PD14 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    Delay(0x3FFFFF);
    Delay(0x3FFFFF);
  
    /* PD14 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    /* Insert delay */
    Delay(0x3FFFFF);
    
    /* PD15 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    
    /* Insert delay */
    Delay(0x7FFFFF);
    
    GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
    
    /* Insert delay */
    Delay(0xFFFFFF);
    //InstantRodos instantRodos;
    //instantRodos.instantMain();
}


void USART_PutChar(char c)
{
    // Wait until transmit data register is empty
    while (!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
    // Send a char using USART3
    USART_SendData(USART3, c);
}


void USART_PutString(char *s)
{
    // Send a string
    while (*s)
    {
        USART_PutChar(*s++);
    }
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
  
extern "C" void mprintf(char *format, ...);
  
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  configureTheTimer() ;
  
   USART_Config();
  
  USART_PutChar('M');
  USART_PutString((char *)"Hello Mike and Faisal");

  ThreadWithTimer tw1;
  // ThreadWithTimer tw2;
  IdleTask hw; 
  
  
  
  Thread::startThreads();
  while(true) {} 
  return 1;
 
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
