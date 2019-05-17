# Quentin's MortarBoard Project

## About

I wanted to have a cool mortarboard for graduation. I wanted to make it easy for my family to see me. I wanted to prove that I learned _something_ while at college. When I 
discovered the wonders of the [relatively cheap RGB matrix panels][1] avalible on sites like sparkfun, I knew what I had to do.

[1]:https://www.sparkfun.com/products/14824

## Hardware

To use this code you will need a SmartMatrix compatible LED board, a SmartMatrix Sheild, a Teensy, and 
a 5v power source with decent current.

You _can_ run the board just using the USB power from the Teensy, but the colors will be off as the 
board will be essentially in a constant state of brown-out. If you go this route, I reccomend not going 
above about 30% of max brightness.


## Installation
Connect the Teensy to a computer via the micro USB port. Open `MortarBoard.ino` in the [Arduino IDE][2] and compile to the device.

Note that you will also need [Teensyduino][3] installed.


[2]:https://www.arduino.cc/en/Main/Software
[3]:https://www.pjrc.com/teensy/td_download.html


![My Mortarboard with everything installed](mortarboard.png)

(Comic is [XKCD #74](https://xkcd.com/74/))
