#include "led.h"
#include "stm32l552.h"

void led_init(void)
{
    RCC_AHB2ENR |= RCC_GPIOBEN;
    RCC_AHB2RSTR |= RCC_GPIOBRST;     // Reset high
    RCC_AHB2RSTR &= ~RCC_GPIOBRST;    // Reset low
    GPIOB_MODER &= ~GPIOB7_MODER;     // Reset
    GPIOB_MODER |= (0x01 << 14);      // Set to General purpose output
    GPIOB_OTYPER &= ~GPIOB7;          // Set to type: Output push-pull (7: 0)
    GPIOB_OSPEEDR &= ~GPIOB7_OSPEEDR; // Set to: Very low speed (15, 14: 00)
    GPIOB_PUPDR &= ~GPIOB7_PUPDR; // Set to: No pull up, pull down (15, 14: 00)
}

void led_set_state(bool ledOn)
{
    if(ledOn)
    {
        GPIOB_ODR |= GPIOB7;
    }
    else
    {
        GPIOB_ODR &= ~GPIOB7;
    }
}