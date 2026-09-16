#include "LPC17xx.h"

void configPines(void);
void configInt(void);

int main (void){
    configPines();
    configInt();

    while(1){}

}

void configPines(void){

    LPC_PINCON->PINSEL4 |=  (1 << 22);
    LPC_PINCON->PINSEL4 |=  (1 << 24);
    
}

void configInt(void){

LPC_SC->EXTMODE |= (0x6); // EINT1 y EINT2 en modo flanco    
LPC_SC->EXTPOLAR &= ~(1<<1); // EINT1 flanco de bajada
LPC_SC->EXTPOLAR |= (1<<2); // EINT2 flanco de subida
NVIC_EnableIRQ(EINT1_IRQn);
NVIC_EnableIRQ(EINT2_IRQn);

NVIC_SetPriority(EINT1_IRQn, 1);    
NVIC_SetPriority(EINT2_IRQn, 2); // EINT1 tiene mayor prioridad que EINT2

}

void EINT1_IRQHandler(void){

    LPC_SC->EXTINT = (0x2); //Limpio la bandera de EINT1

    SysTick->LOAD = 2499999;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x07; 
    
}

void EINT2_IRQHandler(void){
    LPC_SC->EXTINT = (0x4);
    SysTick->LOAD = 5999999;
        SysTick->VAL = 0;
    SysTick->CTRL = 0x07; 

}