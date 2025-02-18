#include "led.h"

#include <stdint.h>

int main(void)
{
    led_init();

    while(1)
    {
        led_set_state(true);
        for(int i = 0; i < 500000; i++); // arbitrary delay
        led_set_state(false);
        for(int i = 0; i < 500000; i++); // arbitrary delay
    }
}