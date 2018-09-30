#ifndef GPIO_H
#define GPIO_H
void exportPin(int pinNumber);
void setPinMode(int pinNumber, int pinMode);
int readPinValue(int pinNumber);
#endif