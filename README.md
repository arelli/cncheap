# cncheap
A cheap cnc solution,made of 2 stepper motors and 1 servo,for the 2 axis and the pen actuator, respectively.
There is an arduino sketch (cnc.ino) that needs to be uploaded to the microcontroller using the arduino IDE.There 
are (or will be) a series of programms in python and C to process images from various formats(jpg,png,pbm etc.) and
output a special vector file in txt format,that tells the arduino how to move the cnc axis.You have to send the contents of the
file through Serial Communication to the arduino.This is done via the cu terminal on Linux based systems(see cu man page
for more info about how to pipe output of a command to a serial port).
At the moment my goal is to get the individual pixels from an image with a python program using Python Imaging Library
(http://www.pythonware.com/products/pil/) and write them to a file,that then will be read from a C program that will output
the vector text file(because getting pixel values on c is a bit tricky right now).
