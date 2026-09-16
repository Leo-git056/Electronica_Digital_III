#include "LPC17xx.h"

void configPin(void);
void configInt(void);

int main(void){
    
    configPin();
    configInt();

    while(1){}
}


void configPin(void){

    LPC_PINCON->PINSEL3 &= ~(0xFFFF<<0); //P1.16 al P1.23 como GPIO
    LPC_GPIO1->FIODIR |= (0xFF<<16); //P1.16 al P1.23 como salidas
    LPC_PINCON->PINSEL4 |= (1<<20); //Activo EINT0 en P2.10
    LPC_PINCON->PINSEL4 |= (1<<22); //Activo EINT1 en P2.11
    
}


void configInt(void){
    LPC_SC->EXTMODE |= (1<<1);
    LPC_SC->EXTMODE &= ~(1<<0); 
    LPC_SC->EXTPOLAR |= (1<<1);
    LPC_SC->EXTPOLAR |= (1<<0);
    NVIC_SetPriority(EINT1_IRQn, 1);
    NVIC_SetPriority(EINT0_IRQn, 2); // EINT1 tiene mayor prioridad que EINT0
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    
    

}

void EINT1_IRQHandler(void){
    LPC_SC->EXTINT = (0x2); //Limpio la bandera de EINT1
        LPC_GPIO1->FIOCLR = (0xFF<<16);
    if (NVIC_GetPendingIRQ(EINT0_IRQn)){
             
            LPC_GPIO1->FIOSET = (0x41<<16);
      
    }
    else{
        LPC_GPIO1->FIOSET = (0x61<<16);
    }
        
}

void EINT0_IRQHandler(void){
    LPC_SC->EXTINT = (1 << 0);
}
