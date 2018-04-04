#include "gpiote.h"
#include "gpio.h"
#include "ppi.h"

void gpiote_init (void) {

  GPIOTE->CONFIG[0] =  (1<<20) | (2<<16) | (17 << 8) | (1); // GPIOTE kanal 1 til knapp A, setter knapp a til event
  GPIOTE->CONFIG[1] = (0<<20) | (3<<16) | (13 << 8) | (3); // GPIOTE kanal 2 til led strøm 13, setter led til task
  GPIOTE->CONFIG[2] = (0<<20) | (3<<16) | (14 << 8) | (3); // GPIOTE kanal 2 til led strøm 14, setter led til task
  GPIOTE->CONFIG[3] = (0<<20) | (3<<16) | (15 << 8) | (3); // GPIOTE kanal 2 til led strøm 15, setter led til task

}

void ppi_init (void) {
  PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]); //kobler knapp a til forsyningsspenning 13 til LED
  PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]); //aka event=btnA -> task=spg13

  PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]); //kobler knapp a til forsyningsspenning 14 til LED
  PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]); //aka event=btnA -> task=spg14

  PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]); //kobler knapp a til forsyningsspenning 15 til LED
  PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]); //aka event=btnA -> task=spg15

  PPI->CHENSET = (1<<0) | (1<<1) | (1<<2);
}
