#include "uart.h"
#include "gpio.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    uart_init();

    GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
    for (int i = 17; i <= 20; i++) {
		GPIO->PIN_CNF[i] = 1;
	}
    bool ledOn = true;

    int sleep = 0;
	while(1){
		uint32_t temp = GPIO->IN;
		if (!(1 & temp >> 13)) {
			uart_send('A');
            if (ledOn) {
                GPIO->OUTCLR = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                ledOn = false;
            } else {
                GPIO->OUTSET = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                ledOn = true;
            }
		}
		else if (!(1 & temp >> 14)) {
			uart_send('B');
            if (ledOn) {
                GPIO->OUTCLR = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                ledOn = false;
            } else {
                GPIO->OUTSET = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                ledOn = true;
            }
		}

		sleep = 1000000;
		while(--sleep); // Delay
	}
    return 0;
}