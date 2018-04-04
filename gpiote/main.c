#include <stdint.h>
#include <stdio.h>
#include "gpiote.h"
#include "gpio.h"

#define BtnA 17
#define BtnB 26

int main(){

  // Konfigurer LED Matrise
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

  gpiote_init();

  ppi_init();

	while(1){
    int buzy = 0;
    buzy++;
  }
	return 0;
}
