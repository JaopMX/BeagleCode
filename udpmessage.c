#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include "udpmessage.h"

#define SERVER "192.168.64.64"
#define BUFLEN 3  //Max length of buffer
#define PORT 8888   //The port on which to send data

unsigned short msgId = 0x0000;
unsigned short msgType = 0xCAFE;

unsigned short msgUP = 0xBEBF;
unsigned short msgRIGHT = 0xBEC0;
unsigned short msgDOWN = 0xBEC1;
unsigned short msgLEFT = 0xBEC2;

struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
unsigned short message[BUFLEN];

void die(char *s)
{
    perror(s);
    exit(1);
}

void createSocket(){
    s = -1;
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
}

void createSocketAddress(){
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
}

void sendMessage(unsigned short message[], int messageSizeInBytes){
    if (sendto(s, message, messageSizeInBytes , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
}

unsigned short* readMessage(int bufferLength){
    unsigned short buf[bufferLength];
    memset(buf,'\0', bufferLength);
    //try to receive some data, this is a blocking call
    if (recvfrom(s, buf, bufferLength, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
        die("recvfrom()");
    }
    return buf;
}