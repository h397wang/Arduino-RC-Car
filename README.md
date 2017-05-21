# Arduino-RC-Car

#Design
Uses a remote controller Arduino library to facilitate the reading of IR signals.
Each button on the remote controller corresponds to some basic function for the car: accelerate, deaccelerate, stop etc.

#Results
Unidentical wheels have different frictions and torque causing a constant veer

This can be nullified by biasing the analog signals to the dc motors

Got the joystick controller working with it as well

The encoded info from the position of the joy stick is used as input to flicker the IR LED to control the velocity of the car

Unforturnately the range is very limited, and the LED has to "point" directly to the IR receiver (which only receives on one plane).


#Hindsight
Pretty much what I expected from using cheap china made parts.

![alt text](https://github.com/h397wang/Arduino-RC-Car/blob/master/IMG_20160903_210949.jpg)
![alt text](https://github.com/h397wang/Arduino-RC-Car/blob/master/IMG_20160903_211002.jpg)
![alt text](https://github.com/h397wang/Arduino-RC-Car/blob/master/IMG_20160903_211010.jpg)
![alt text](https://github.com/h397wang/Arduino-RC-Car/blob/master/IMG_20160903_211032.jpg)


