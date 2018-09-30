import Adafruit_BBIO.GPIO as GPIO
import time

def shiftSeq(array, newVal):
    for i in range(len(array) - 1):
        array[i] = array[i+1]
    array[len(array) - 1] = newVal
    return array

def arrayMatches(goal, current):
    print "Goal: {} - Current: {}".format("".join(goal), "".join(current))
    if goal == current:
        return True
    return False

def initPins():
    GPIO.setup("P8_7", GPIO.IN)
    GPIO.setup("P8_8", GPIO.IN)
    GPIO.setup("P8_10", GPIO.IN)
    GPIO.setup("P8_9", GPIO.IN)

if  __name__=="__main__":
    initPins()
    letters = ["G","E","I","Q"]
    exitSeq = ["Q","I","E","G"]
    auxSeq = ["","","",""]

    pins = [7,8,10,9]

    breakLoop = False

    while not(breakLoop):
        for i in range(len(letters)):
            time.sleep(.2)
            if GPIO.input("P8_" + str(pins[i])):
                print "Pin {}: {}".format(pins[i],letters[i])
                auxSeq = shiftSeq(auxSeq, letters[i])
                if arrayMatches(exitSeq, auxSeq):
                    breakLoop = True

    