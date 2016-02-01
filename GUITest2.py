"""
Code for live plotting of data from Arduino
"""

# The code was derived from: http://stackoverflow.com/questions/7546050/switch-between-two-frames-in-tkinter

# import matplotlib
# matplotlib.use("TkAgg")
# from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# from matplotlib.figure import Figure
# import matplotlib.animation as animation
# import matplotlib.pyplot as plt 
# import Tkinter as tk

import sys, serial, argparse
import matplotlib.pyplot as plt 
import matplotlib.animation as animation

import ttk, csv, serial, sys, argparse
from os import path


LARGE_FONT= ("Verdana", 12)

# f = Figure(figsize=(5,4), dpi=100)
# data_plot = f.add_subplot(121)
# derivitive_plot = f.add_subplot(122)


# plot class
class AnalogPlot:
	# constr
	def __init__(self, strPort, interval, filename):
		# open serial port
		self.ser = serial.Serial(strPort, 9600)
		self.int = interval
		self.filename = filename

		self.tx = []
		self.py = []
		self.dy = []

		self.createFile()

	# add data
	def add(self, data):
		if self.tx == []:
			self.tx.append(self.int/2.0)
		else:
			self.tx.append(self.tx[len(self.tx)-1]+self.int)
		self.py.append(data)
		if (len(self.py) >= 2):
			length = len(self.py)
			self.dy.append((self.py[length-1] - self.py[length-2])/float(self.int))
		else:
			self.dy.append(0.0)
		# print 'dataAdded'
		# print self.py

	# update plot
	def update(self, frameNum, a0, a1):
		try:
			data = self.readData()
			self.add(data)
			self.writeData(data)
			a0.clear()
			a1.clear()
			a0.plot(self.tx, self.py)
			a1.plot(self.tx, self.dy)
		except KeyboardInterrupt:
			print 'exiting'

		return a0, 

	def createFile(self):
	    fd = open(self.filename,'wb')
	    fd.close()

	def readData(self):
	    counter = 0
	    data = []
	    while counter < self.int*2:
	        if (self.ser.inWaiting()):
	            data.append(float(self.ser.readline()))
	            counter += 1
	    avg = sum(data)/float(len(data))
	    # print "Dataread: ", avg
	    return avg

	def writeData(self, data):

	    with open(self.filename,'a') as csvfile:
	        writer = csv.writer(csvfile, delimiter = ',')
	        dataToWrite = [self.tx[len(self.tx)-1], data, self.dy[len(self.dy)-1]]
	        # print dataToWrite
	        writer.writerow(dataToWrite)
	        csvfile.close()
	        # print "DataWritten"


	# clean up
	def close(self):
		# close serial
		self.ser.flush()
		self.ser.close()

def main():
	# create parser
	parser = argparse.ArgumentParser(description="LDR serial")
	# add expected arguments
	parser.add_argument('--port', dest='port', required=True)
	parser.add_argument('--int' , dest='interval', required=True)
	parser.add_argument('--fn'  , dest='filename', required=True)



	# parse args
	args = parser.parse_args()

	#strPort = '/dev/tty.usbserial-A7006Yqh'
	strPort = args.port
	Int = int(args.interval)
	strFilename = args.filename

	print('reading from serial port %s...' % strPort)

	# print("Testpoint 1")
	# plot parameters
	analogPlot = AnalogPlot(strPort, Int, strFilename)
	# print("Testpoint 2")

	print('plotting data...')

	# set up animation
	# fig = plt.figure()
	# ax = plt.axes(xlim=(0, 100), ylim=(-5, 2))
	# a0, = ax.plot([], [])
	# a1, = ax.plot([], [])
	# anim = animation.FuncAnimation(fig, analogPlot.update, 
	#                              fargs=(a0, a1), 
	#                              interval=50)

	fig = plt.figure()
	a0 = fig.add_subplot(121)
	a1 = fig.add_subplot(122)
	anim = animation.FuncAnimation(fig, analogPlot.update, 
	                             fargs=(a0, a1), 
	                             interval=50)


	# show plot
	plt.show()

	# clean up
	analogPlot.close()

	print('exiting.')
  

# call main
if __name__ == '__main__':
	main()
