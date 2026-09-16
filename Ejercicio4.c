#include "sdtint.h"  
#include "stdio.h"  
#include "LPC17xx.h"

void configGPIO(void);
const char* identificarPulsador(void);
void retardo(uint32_t tiempo);


int main(void){
const char* pulsador;
configGPIO();
while(1){
   pulsador =  identificarPulsador();
   printf("Pulsador presionado: %s\n", pulsador);
   retardo(10000000); // Retardo de 1 segundo
    }
}


void configGPIO(void){
    
    LPC_PINCON->PINSEL0 &= ~(0xF << 0); // Configura P0.0 y P0.1 como GPIO
    LPC_GPIO0->FIODIR &= ~(0x3 << 0); // Configura P0.0 y P0.1 como entradas
    LPC_PINCON->PINMODE0 &= ~(0xF << 0); // Configura P0.0 y P0.1 con resistencias pull-up
    
}

const char* identificarPulsador(void){
        
     if((LPC_GPIO0->FIOPIN & (0x1 << 0 )) == 0 && ((LPC_GPIO0->FIOPIN & (0x2 << 0 )) == 0)){
        return "Pulsador 1 y 2";
    }
    else if((LPC_GPIO0->FIOPIN & (0x1 << 0 )) == 0){
        return "Pulsador 1";
    }
    else if((LPC_GPIO0->FIOPIN & (0x2 << 0)) == 0){
        return "Pulsador 2";
    }
   
    else{
        return "Ninguno";
    }
}
void retardo(uint32_t tiempo){
   volatile uint32_t i;
    for(i=0; i<tiempo; i++);
}
