#include "led.h"
#include "stm32f10x.h"
#include "delay.h"
void led_init()
	{
 
		RCC->APB2ENR|=1<<2;                 
    GPIOA->CRL&=0X00000000;   
    GPIOA->CRL|=0X33333333;     
    GPIOA->ODR|=1<<2;  
	}

void  led_shansuo()
{
	LED0 = ~LED0;
	delay_ms(100);
	LED0 = ~LED0;
	delay_ms(100);
}
