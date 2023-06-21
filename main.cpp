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
#include "InstantRodos.h"
#include "IdleTask.h"
#include "ThreadWithTimer.h"


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


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
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
