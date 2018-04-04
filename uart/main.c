#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"

#define BtnA 17
#define BtnB 26

ssize_t _write(int fd, const void *buf, size_t count){
        char * letter = (char *)(buf);
        for(int i = 0; i < count; i++){
                uart_send(*letter);
								letter++;
				}
				return count;
}

int main(){
	//set opp transaksjon
	uart_init();

	// Konfigurer LED Matrise
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Konfigurer knapper
	GPIO->PIN_CNF[BtnA] = 0; // Btn A
	GPIO->PIN_CNF[BtnB] = 0; // Btn B

	//tester print-funksjonen
	iprintf("Norway has %d counties.\n\r", 18);

	int sleep = 0;

	while(1){
			// Lytt etter sendte pakker fra pc
			char rx = uart_read();

			// Send pakker tilbake til pc
			uart_send(rx);

			// Hvis det sendes en bokstav fra pc
			if(rx != '\0'){
				for(int i = 13; i <= 15; i++){
					//led er på
					if( (GPIO->OUT & (1 << i)) >> i){
							//skru av led
							GPIO->OUTCLR = (1 << i);
					//led er av
					}else{
							//skru på LED
							GPIO->OUTSET = (1 << i);
					}
				}
			}

			// BtnA trykkes
			if (((GPIO->IN & (1 << BtnA)) >> BtnA) == 0) {
				//send en bokstav
        uart_send('A');
			}

			// BtnB trykkes
			if(((GPIO->IN & (1<<BtnB))>>BtnB) == 0) {
				//send en bokstav
        uart_send('B');
		  }

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
