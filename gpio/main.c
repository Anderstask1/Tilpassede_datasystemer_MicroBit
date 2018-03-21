#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define BtnA 17
#define BtnB 26

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

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
				// Slå av
				for(int i = 13; i <= 15; i++){
					GPIO->OUTCLR = (1 << i);
				}
			}

			// BtnB
			if(((GPIO->IN & (1<<BtnB))>>BtnB) == 0) {
			// Slå på
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1<< i);
			}
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
