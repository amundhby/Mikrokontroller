#include "gpiote.h"
#include "ppi.h"

int main() {
    button_and_ledMatrix_init();

    ppi_init();

    int sleep = 0;
    while(1) {
		sleep = 1000000;
		while(--sleep); // Delay
	}
    return 0;
}