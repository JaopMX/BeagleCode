#include <stdio.h>
#include <stdlib.h>

#define PIN_MODE_OUT 1
#define PIN_MODE_IN 0

void exportPin(int pinNumber){
    char str[80];
    sprintf(str, "echo %d > /sys/class/gpio/export", pinNumber);
    system(str);
}

void setPinMode(int pinNumber, int pinMode){
    if (pinMode == PIN_MODE_OUT){
        char str[80];
        sprintf(str, "echo out > /sys/class/gpio/gpio%d/direction", pinNumber);
        system(str);
    }else if(pinMode == PIN_MODE_IN){
        char str[80];
        sprintf(str, "echo in > /sys/class/gpio/gpio%d/direction", pinNumber);
        system(str);
    }
}

int readPinValue(int pinNumber){
    FILE *fp;
    char value[10];

    /* Open the command for reading. */
    char str[80];
    sprintf(str, "cat /sys/class/gpio/gpio%d/value", pinNumber);
    fp = popen(str, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    int pinValue = -1;
    /* Read the output a line at a time - output it. */
    fgets(value, sizeof(value)-1, fp);
    pinValue = value[0] - '0';

    /* close */
    pclose(fp);

    return pinValue;
}