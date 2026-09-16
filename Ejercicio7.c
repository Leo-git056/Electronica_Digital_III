#include "LPC17xx.h"

void configGPIO(void);
void configInt(void);

volatile uint32_t auxiliar = 0;

int main(void){

configGPIO();
configInt();


while(1){

}

}

void configGPIO(void){

    LPC_PINCON->PINSEL0 &= ~(0x3); //P0.0 como GPIO
    LPC_PINCON->PINSEL4 &= ~(0x3); //P2.0 como GPIO
    LPC_GPIO0->FIODIR &= ~(1<<0);
    LPC_GPIO2->FIODIR &= ~(1<<0);

}

void configInt(void){
    LPC_GPIOINT->IO0IntEnR |= (0x1);
    LPC_GPIOINT->IO2IntEnR |= (0x1);

    NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void){

    if(LPC_GPIOINT->IO0IntStatR & (1<<0)){
        auxiliar=0b100111;
        LPC_GPIOINT->IO0IntClr = (1<<0);
    }
    else if(LPC_GPIOINT->IO2IntStatR & (1<<0)){
        auxiliar=0b111001011010110;
        LPC_GPIOINT->IO2IntClr = (1<<0);
    }


}