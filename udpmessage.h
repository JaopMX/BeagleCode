#ifndef UDP_MESSAGE
#define UDP_MESSAGE

void die(char *s);
void createSocket();
void createSocketAddress();
void sendMessage(unsigned short message[], int messageSizeInBytes);
unsigned short* readMessage(int bufferLength);

#endif