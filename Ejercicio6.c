#include <stdio.h>
#include <stdint.h>
#include "LPC17xx.h"

#define n 9
uint32_t A[n]={0,1,0,0,1,1,0,1,0};
uint32_t B[n]={0,1,1,1,0,0,1,1,0};

void configGPIO(void);
void configInt(void);
void secuenciaA(void);
void secuenciaB(void);
void retardo(uint32_t tiempo);


int main(void){
configGPIO();
configInt();

while(1){
    //El programa se queda en espera de la interrupcion 

}

}


void configGPIO(void){
    LPC_PINCON->PINSEL0 &= ~(0xF); //P0.0 y P0.1 como GPIO
    LPC_GPIO0->FIODIR |= (0x3); //P0.0 y P0.1 como salidas
    LPC_PINCON->PINSEL4 &= ~(0xF); //P2.0 y P2.1 como GPIO
    LPC_GPIO2->FIODIR &= ~(0x3); //P2.0 y P2.1 como entradas
    LPC_GPIO0->FIOSET = (0x3);

   
}

void configInt(void){
 LPC_GPIOINT->IO2IntEnR |= (0x1<<0); //Habilita interrupciones por flanco de subida en P2.0
 LPC_GPIOINT->IO2IntEnF |= (0x1<<1); //Habilita interrucpciones por flanco de bajada en P2.1
 NVIC_EnableIRQ(EINT3_IRQn);
}

void retardo(uint32_t tiempo){
    volatile uint32_t i;
    for(i=0; i<tiempo; i++);
}

void secuenciaA(void){
    for(int i=0; i<n ; i++){
       if(A[i]==1){
        LPC_GPIO0->FIOSET = (1<<0);
       }
       else{
        LPC_GPIO0->FIOCLR = (1<<0);
       }
       retardo(10000000);
    }
    LPC_GPIO0->FIOSET = (1<<0);
}

void secuenciaB(void){
    for(int i=0; i<n ; i++){
       if(B[i]==1){
        LPC_GPIO0->FIOSET = (1<<1);
       }
       else{
        LPC_GPIO0->FIOCLR = (1<<1);
       }
       retardo(10000000);
    }
     LPC_GPIO0->FIOSET = (1<<1);
}
void EINT3_IRQHandler(void){
    if(LPC_GPIOINT->IO2IntStatR & (1<<0)){ //Si la interrupcion fue hecha por P2.0
        LPC_GPIOINT->IO2IntClr = (1<<0); //Limpia bandera en P2.0
        secuenciaA();
    
    }
    else if(LPC_GPIOINT->IO2IntStatF & (1<<1)){ //Si la interrupcion fue hecha por P2.1
        LPC_GPIOINT->IO2IntClr = (1<<1); //Limpia bandera en P2.1
        secuenciaB();
       
    }

}

