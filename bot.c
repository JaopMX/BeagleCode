#include "gpio.h"
#include "udpmessage.h"
#include <stdio.h>

int main(){
    int pines[4] = {66,67,68,69};

    const int QUERY_LENGTH = 2;
    const int QUERY_RESPONSE_LENGTH = 74;

    const int CONTROLLER_MSG_LENGTH = 3;
    const int CONTROLLER_MSG_RESPONSE_LENGTH = 3;

    const int NROWS = 5;
    const int NCOLS = 7;

    unsigned short query[QUERY_LENGTH];
    unsigned short message[CONTROLLER_MSG_LENGTH];
    unsigned short* queryResponse;
    unsigned short* response;
    createSocket();
    createSocketAddress();

    unsigned short queryReqType = 0xFFCA;
    unsigned short queryId = 0x0000;
    unsigned short queryRespDirRight = 0xC0BE;
    unsigned short queryRespDirLeft = 0xC2BE;
    unsigned short queryRespCellEmpty = 0xADDE;
    unsigned short queryRespCellEnemy = 0xAEDE;
    unsigned short queryRespCellFrog = 0xAFDE;

    unsigned short gameGrid[NROWS][NCOLS];
    unsigned short freeGrid = 0x0000;
    unsigned short enemyGrid = 0x0001;
    unsigned short frogGrid = 0x0002;

    unsigned short msgId = 0x0000;
    unsigned short msgType = 0xFECA;
    unsigned short msgUP = 0xBFBE;
    unsigned short msgRIGHT = 0xC0BE;
    unsigned short msgDOWN = 0xC1BE;
    unsigned short msgLEFT = 0xC2BE;

    unsigned short controls[4] = {msgUP, msgRIGHT, msgDOWN, msgLEFT};
    
    while(1){

        query[0] = queryReqType;
        query[1] = queryId++;
        sendMessage(query, QUERY_LENGTH * sizeof(short));
        queryResponse = readMessage(QUERY_RESPONSE_LENGTH);

        
        for(int i = 5; i < QUERY_RESPONSE_LENGTH; i = i + 2)
        {
            if(queryResponse[i] == queryRespCellEmpty){
                //TODO
            }else if(queryResponse[i] == queryRespCellEnemy){
                //TODO
            }else if(queryResponse[i] == queryRespCellFrog){
                //TODO
            }
        }
        

        for(int i = 0; i < 4; i++)
        {
            int valueFromPin = readPinValue(pines[i]);
            if (valueFromPin){
                message[0] = msgType;
                message[1] = msgId++;
                message[2] = controls[i];
                //sendMessage(message);
                //response = readMessage();
                printf("Sent: [0x%X,0x%X,0x%X]\n" , message[0], message[1], message[2]);
                printf("Received: [0x%X,0x%X,0x%X]\n" , response[0], response[1], response[2]);
                //if (response[2] == 0xC0E0)
                //    return 0;
            }
        }
    }

}