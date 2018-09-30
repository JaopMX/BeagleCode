#include "gpio.h"
#include "udpmessage.h"
#include <stdio.h>
#include <unistd.h>

int main(){
    int pines[4] = {66,67,68,69};
    unsigned short message[3];
    unsigned short* response;
    createSocket();
    createSocketAddress();

    unsigned short msgId = 0x0000;
    unsigned short msgType = 0xFECA;

    unsigned short msgUP = 0xBFBE;
    unsigned short msgRIGHT = 0xC0BE;
    unsigned short msgDOWN = 0xC1BE;
    unsigned short msgLEFT = 0xC2BE;

    unsigned short controls[4] = {msgUP, msgRIGHT, msgDOWN, msgLEFT};
    
    while(1){
        for(int i = 0; i < 4; i++)
        {
            int valueFromPin = readPinValue(pines[i]);
            if (valueFromPin){
                message[0] = msgType;
                message[1] = msgId++;
                message[2] = controls[i];
                sendMessage(message, 6);
                response = readMessage(3);
                printf("Sent: [0x%X,0x%X,0x%X]\n" , message[0], message[1], message[2]);
                printf("Received: [0x%X,0x%X,0x%X]\n" , response[0], response[1], response[2]);
                usleep(100*1000);
                //if (response[2] == 0xC0E0)
                //    return 0;
            }
        }
    }

}