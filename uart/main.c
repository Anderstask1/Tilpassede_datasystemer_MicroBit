#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define BtnA 17
#define BtnB 26

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BtnA] = 0; // Btn A
	GPIO->PIN_CNF[BtnB] = 0; // Btn B

	int sleep = 0;
	while(1){
			// BtnA
			if (((GPIO->IN & (1<<BtnA))>>BtnA) == 0) {
				// Slå av led-lys
				for(int i = 13; i <= 15; i++){
					GPIO->OUTCLR = (1 << i);
				}
        uart_init();
        uart_send('A');
			}

			// BtnB
			if(((GPIO->IN & (1<<BtnB))>>BtnB) == 0) {
  			// Slå på led-lys
  			for(int i = 13; i <= 15; i++){
  				GPIO->OUTSET = (1<< i);
  			}
        uart_init();
        uart_send('B');
		  }

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
