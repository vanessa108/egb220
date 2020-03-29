# egb220
EGB220 Team C2 - line following robot

The Arduino IDE is based of C++ which means we can make use of classes in our code. This means we can have header files (.h)(functions defined in one file that can be used in another file) and within those, we can create classes (.cpp) that contain our functions etc.

## File overview

* The main.ino is an Arduino sketch file - this is what the Arduino and where our main program is written. All the line following is currently written in this file. 
* The spark.h file is a header file that contains pin map conversions from the Spark to the Arduino Leo board 
* The motors.h and motors.cpp contains the motor class. This has all the functions for the set up/control of the motors
* The sensors.h and sensors.cpp contiants the sensor class. This has all the functions to set up and read from the sensors. 

We will hopefully have another class for the LCD later on :))

## Adding your code
I would recommend getting [Github desktop] (https://desktop.github.com/) to make using github a little easier. Once you sign in with your details, go to *Clone repository* and clone this repository (egb220). This will download a version of this code to your computer. **BEFORE ADDING CODE** make sure to click *Fetch origin* or *Pull* to get the lastest changes. Once you have finished and made some progress you can *commit* your code (this will update your changes/additions), it's generally good practice when committing to add a small summary/description of the progress you've made (i.e. configured motor input/output). Then you need to *Push* to update your changes - **make sure to do this** or your code won't be updated for everyone else!! 
