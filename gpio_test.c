#include <stdio.h>
#include "gpio.h"

char bufferAux[4];
int pines[4] = {66,67,68,69};
char letras[4] = {'G','E','I','Q'};
char bufferSalida[4] = {'G','E','I','Q'};

void shiftArray(int newVal){
    for(int i = 0; i < 3; i++){
        bufferAux[i] = bufferAux[i+1];
    }
    bufferAux[3] = newVal;
}

int arrayMatches(){
    
    printf("Goal: %s - Current: %s\n",bufferSalida, bufferAux);

    for(int i = 0; i < 4; i++)
    {
        if(bufferAux[i] != bufferSalida[i])
            return 0;
    }
    return 1;
}

int main(){
    /*
    for (int i = 0; i < 4; i++){
        exportPin(pines[i]);
        printf("Pin %d exportado", pines[i]);
    }*/
    while(1){
        for(int i = 0; i < 4; i++)
        {
            int valueFromPin = readPinValue(pines[i]);
            //printf("Pin %d value: %d\n",pines[i],valueFromPin);
            if(valueFromPin){
                printf("%c\n",letras[i]);
                shiftArray(letras[i]);
                if(arrayMatches())
                    return 0;
            }
            //sleep(.1);
        }
    }

    return 0;
}