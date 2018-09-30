import Adafruit_BBIO.GPIO as GPIO
import socket
import time
import array

def ByteToHex( byteStr ):
    return ''.join( [ "%02X " % ord( x ) for x in byteStr ] ).strip()

def initPins():
    GPIO.setup("P8_7", GPIO.IN)
    GPIO.setup("P8_8", GPIO.IN)
    GPIO.setup("P8_10", GPIO.IN)
    GPIO.setup("P8_9", GPIO.IN)

def createSocket():
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

if  __name__=="__main__":
    initPins()
    socket = createSocket()

    UDP_IP = "192.168.7.1"
    UDP_PORT = 8888

    msgId1 = 0x00
    msgId2 = 0x00
    msgType1 = 0xFE
    msgType2 = 0xCA

    msgUP1 = 0xBF
    msgUP2 = 0xBE

    msgRIGHT1 = 0xC0
    msgRIGHT2 = 0xBE

    msgDOWN1 = 0xC1
    msgDOWN2 = 0xBE

    msgLEFT1 = 0xC2
    msgLEFT2 = 0xBE


    controls = [msgUP1,msgUP2,msgRIGHT1,msgRIGHT2,msgDOWN1,msgDOWN2,msgLEFT1,msgLEFT2]

    pins = [7,8,10,9]

    breakLoop = False

    while not(breakLoop):
        for i in range(len(controls)/2):
            time.sleep(.01)
            if GPIO.input("P8_" + str(pins[i])):
                message = str(bytearray([msgType1,msgType2,msgId1,msgId2,controls[2*i],controls[2*i + 1]]))
                socket.sendto(message, (UDP_IP, UDP_PORT))
                print "Sent: " + ByteToHex(message)
                data, addr = socket.recvfrom(512) # buffer size is 1024 bytes
                print "Received:" + ByteToHex(data)

    