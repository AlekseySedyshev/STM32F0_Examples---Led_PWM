#include "stm32f0xx.h"        // Device header

uint8_t i,flag=0;

void delay_ms (uint16_t value)
{
    TIM17->ARR = value;
    TIM17->CNT = 0;
    TIM17->CR1 = TIM_CR1_CEN;
    while((TIM17->SR & TIM_SR_UIF)==0){}
		TIM17->SR &= ~TIM_SR_UIF;
}

void initial (void)
{
	/*timer config*/
  RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;    						//HSI 8 MHz - 1 msek
  TIM17->PSC = 8000-1;
  TIM17->CR1 |= TIM_CR1_OPM;
	
	/*GPIOB PIN 0 - Alternative mode */ 
	RCC->AHBENR  |= RCC_AHBENR_GPIOBEN; 								//
	GPIOB->MODER |= GPIO_MODER_MODER0_1; 								// alternative
	GPIOB->AFR[0] |= 0x01 << GPIO_AFRL_AFRL0_Pos;  			//Pb0 - Alternative

	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
	TIM3->PSC = 1;  																		// 8MHZ - in
	TIM3->ARR = 100; 	 
	TIM3->CCR3 = 0;  
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
	TIM3->CCER |= TIM_CCER_CC3E; 
 	TIM3->CR1 |= TIM_CR1_CEN;
	TIM3->EGR |= TIM_EGR_UG;
	} 

int main(void)
{
initial();

//-----------------------------initial data----------------------------------

while (1)  /* Main loop */
{

for (i=0;i<100;i++)
{
	TIM3->CCR3 = i;
	delay_ms(10);
}

for (i=100;i>0;i--)
{
	TIM3->CCR3 = i;
	delay_ms(10);
}

} // end - main loop 
} // end - Main  
	
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ while (1)  {  } }
#endif
