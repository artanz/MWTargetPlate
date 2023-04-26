/*
  Target Plate Version 1_1, Dec 15 2017
  John Harkey
  
  This is a simple sketch to demonstrate the use of analogComp, a
  library to manage the analog comparator included in a wide
  variety of Atmel microcontrollers

  This sketch enables an interrupt to be raised when on the analog input 0
  (pin AIN0) there is a voltage greater than the voltage on the
  analog input 1 (pin AIN1). To test the sketch, build the following
  circuit:
  - connect pin AIN1 to pin 3V3
  - connect pin AIN0 to GND using a pull-down resistor (10Kohm or greater)
  - connect pin AIN0 to pin 5V to activate the interrupt


  More info on the analog comparator can be found reading the datasheet.

  Please read the README file to know how to use this library.

  Written by Leonardo Miliani <leonardo AT leonardomiliani DOT com>

  This code and the analogComp library are free software; you can redistribute
  and/or modify them under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 3.0 of the License,
  or (at your option) any later version.

  This work is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

//include the library
#include "analogComp.h"


//global variables
const byte WHT_LED4 = 4; //set the output LED
const byte IR_LED3 = 3;
const byte HIT_L = 2; //active low output indicates plate was hit

boolean enableLed = false; //used to check if the interrupt has raised

//set up the hardware
void setup() {
  
  pinMode(WHT_LED4, OUTPUT); //LED pin as output
  pinMode(HIT_L, OUTPUT);
  digitalWrite(WHT_LED4, HIGH);
  digitalWrite(HIT_L, HIGH);
  analogComparator.setOn(AIN0, AIN1); //we instruct the lib to use voltages on the pins
  analogComparator.enableInterrupt(changeStatus, CHANGE); //we set the interrupt and when it has to be raised

}





//main loop
void loop() {

  if (enableLed) { //check if the analog comparator has raised the interrupt
    //yes, so we do a little blink of the LED
    digitalWrite(WHT_LED4, LOW);
    digitalWrite(HIT_L, LOW);
    delay(30);
    digitalWrite(HIT_L, HIGH);
    delay(100);
    digitalWrite(WHT_LED4, HIGH);
    enableLed = false;
  }
}

//interrupt to be raised by the analog comparator
void changeStatus() {
  enableLed = true; //inform the main loop that the condition has been reached by the analog comparator
}
