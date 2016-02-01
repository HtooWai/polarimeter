"""
	Htoo Wai Htet
"""

import serial                   				# serial library must be installed; used for serial communication
import csv										# csv library is built-in; used for creating csv files

arduino = serial.Serial()
interval = 1                                  # how many seconds between each sample
filename = 'data.csv'                           # file name


def createFile():
    fd = open(filename,'wb')
    fd.close()

def openPort():
    arduino.baudrate = 9600						# sets the baude rate: 9600 is the common rate
    arduino.port = '/dev/cu.usbmodem1411'		# change ths value accordinly
    arduino.timeout = 1
    arduino.open()
    return

def closePort():
    arduino.close()
    return

def readData(samples):
    data = []
    counter = 0
    while counter < samples:
        if (arduino.inWaiting()):
            data.append(float(arduino.readline()))
            counter += 1
    avg = sum(data)/float(len(data))
    print "exitted"
    return avg

def writeData(filename,timestamp, data):

    fd = open(filename,'a')
    dataToWrite = str(timestamp) + "," + str(data) + "\r"
    fd.write(dataToWrite)
    fd.close()
    timestamp += interval
    return timestamp

def main():
    openPort()
    createFile()
    samples  = interval * 2                     # becuase data is collected every 500ms
    timestamp = interval/2.0
    while True:
        data = readData(samples)
        writeData(filename, timestamp, data)
        timestamp += interval
        print data

main()
