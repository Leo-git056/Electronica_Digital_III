#include "LPC17xx.h"

#define n 8 // cantidad de datos a promediar





void configGPIO(void);
void lecturaDatos(int16_t arr[]);
void borrarViejo(int16_t arr[]);
void agregarNuevo(int16_t arr[]);
int16_t calculoPromedio(int16_t arr[]);
void mostrarPromedio(int16_t promedio);
void retardo(uint32_t tiempo);


int main (void){
    int16_t datos[n] = {0};

    int16_t promedio = 0;
    configGPIO();
    lecturaDatos(datos);
    while(1){
        
        borrarViejo(datos);
        agregarNuevo(datos);
        promedio = calculoPromedio(datos);
        mostrarPromedio(promedio);

        retardo(100000000);   
    }


}



void configGPIO(void){

    LPC_PINCON->PINSEL4 &= ~(0xFFFFFFFF); // Configura P2.0 a P2.15 como GPIO;    
    LPC_PINCON->PINSEL0 &= ~(0xFFFFFF); // Configura P0.0 a P0.11 como GPIO;
    LPC_PINCON->PINSEL0 &= ~(0x3 <<30); // Configura P0.15 como GPIO;    
    LPC_PINCON->PINSEL1 &= ~(0x3F << 0); // Configura P0.16 a P0.18 como GPIO;

    LPC_GPIO2->FIODIR &= ~(0xFFFF); 
    LPC_GPIO0->FIODIR |= (0xFFF << 0); // Configura P0.0 a P0.11 como salidas
    LPC_GPIO0->FIODIR |= (0x1 << 15); // Configura P0.15 como salida
    LPC_GPIO0->FIODIR |= (0x7 << 16); // Configura P0.16 a P0.18 como salidas

}

void lecturaDatos(int16_t arr[]){
    int16_t i;
    for(i=0; i<n; i++){
        arr[i] = (LPC_GPIO2->FIOPIN & (0xFFFF)); // Lee los datos de P2.0 a P2.15
    }

}

void borrarViejo(int16_t arr[]){
    int16_t i;
    for(i=0; i<n-1; i++){
        arr[i] = arr[i+1];
    }
   
}
void agregarNuevo(int16_t arr[]){
     arr[n-1] = LPC_GPIO2->FIOPIN & (0xFFFF); // Lee los datos de P2.0 a P2.15
}
int16_t calculoPromedio(int16_t arr[]){
    int32_t sumador = 0;
    for(int16_t i=0; i<n ; i++){
        sumador = ((sumador + arr[i]));
     
    }
    return sumador/n;
}

void mostrarPromedio(int16_t promedio){
uint32_t mascara = 0x00078FFF;  
uint32_t b0_11 = promedio & 0xFFF; // Obtiene los bits 0 a 11 del promedio 
uint32_t b12_15 = (promedio & 0xF000);
uint32_t salida = b0_11 | (b12_15 << 3); // Combina los bits para la salida
LPC_GPIO0->FIOCLR = mascara; 
LPC_GPIO0->FIOSET = salida; 
}

void retardo(uint32_t tiempo){
   volatile uint32_t i;
    for(i=0; i<tiempo; i++);
}