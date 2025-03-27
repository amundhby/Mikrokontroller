#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	// Fill inn the configuration for the remaining buttons
	for (int i = 17; i <= 20; i++) {
		GPIO->PIN_CNF[i] = 1;
	}
}

int main(){
	// Configure LED Matrix
	/*for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}*/

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while(1){
		uint32_t temp = GPIO->IN;
		if (!(1 & temp >> 13)) {
			GPIO->OUTCLR = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
			//1 & temp >> 13
			// !(GPIO->IN & 1 << 13)
		}
		else if (!(1 & temp >> 14)) {
			GPIO->OUTSET = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
			//1 & temp >> 14
			// !(GPIO->IN & 1 << 14)
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}