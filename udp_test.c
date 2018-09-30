#include "udpmessage.h"
#include <stdio.h>

int main(){
    unsigned short message[3];
    createSocket();
    createSocketAddress();
    message[0] = 0xCAFE;
    message[2] = 0xBEBF;
    unsigned short* bufferTest;
    unsigned short msgId = 0x0000;
    while(1)
    {
        message[1] = msgId++;
        getchar();
        sendMessage(message);
        bufferTest = readMessage();
        printf("Data: [0x%X,0x%X,0x%X]\n" , bufferTest[0], bufferTest[1], bufferTest[2]);
    }
    return 0;
}