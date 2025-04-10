#include "gpio.h"
#include "gpiote.h"

void button_and_ledMatrix_init() {
  GPIO->PIN_CNF[13] = (3 << 2);

  GPIOTE->CONFIG[0] = (1) | (13 << 8) | (2 << 16);

  for (int i = 17; i <= 20; i++) {
		/*GPIO->PIN_CNF[i] = 1;
    GPIO->OUTSET = (1 << i);*/
    GPIO->PIN_CNF[i] = (3 << 2);
    GPIOTE->CONFIG[i-16] = (3) | (i << 8) | (3 << 16) | (1 << 20);
	}
}