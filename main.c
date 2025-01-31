#include <stdint.h>

// Register address
#define RCC_BASE 0x40021000
#define GPIOB_BASE  0x42020400

#define RCC_AHB2ENR     *(volatile uint32_t *)(RCC_BASE + 0x4C)
#define RCC_AHB2RSTR    *(volatile uint32_t *)(RCC_BASE + 0x2C)
#define GPIOB_MODER     *(volatile uint32_t *)(GPIOB_BASE)
#define GPIOB_OTYPER    *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_OSPEEDR   *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_PUPDR     *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_ODR       *(volatile uint32_t *)(GPIOB_BASE + 0x14)

// Bitmasks
#define RCC_GPIOBEN (1<<1)
#define RCC_GPIOBRST (1<<1)
#define GPIOB7 (1UL<<7)
#define GPIOB7_MODER (3UL<<14)
#define GPIOB7_OSPEEDR (3UL<<14)
#define GPIOB7_PUPDR (3UL<<14)

int main(void) 
{
    RCC_AHB2ENR |= RCC_GPIOBEN;
    RCC_AHB2RSTR |= RCC_GPIOBRST; // Reset high
    RCC_AHB2RSTR &= ~RCC_GPIOBRST; // Reset low
    GPIOB_MODER &= ~GPIOB7_MODER; // Reset
    GPIOB_MODER |= (0x01 << 14); // Set to General purpose output
    GPIOB_OTYPER &= ~GPIOB7; // Set to type: Output push-pull (7: 0)
    GPIOB_OSPEEDR &= ~GPIOB7_OSPEEDR; // Set to: Very low speed (15, 14: 00)
    GPIOB_PUPDR &= ~GPIOB7_PUPDR; // Set to: No pull up, pull down (15, 14: 00)

    while(1)
    {
        GPIOB_ODR |= GPIOB7;
        for (int i = 0; i < 500000; i++); // arbitrary delay
        GPIOB_ODR &= ~GPIOB7;
        for (int i = 0; i < 500000; i++); // arbitrary delay
    }
}