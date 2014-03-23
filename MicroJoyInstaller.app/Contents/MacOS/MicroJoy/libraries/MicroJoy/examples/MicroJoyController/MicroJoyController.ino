/*
================================================================================
MicroJoy

(c) Jon Lidgard 2014

  The MicroJoy library enables the SparkFun ProMicro to be used as a joystick.
  Thanks to Alan Chathan for using the LeoJoy code as a reference.

** IMPORTANT **

If you run MicroJoyInstaller it will patch HID.cpp automatically, otherwise:
Modify HID.cpp inside 'Resources/Java/hardware/arduino/cores/arduino/HID.cpp'

extern const u8 _hidReportDescriptor[] PROGMEM;

>>> REPLACE WITH THIS NEW _hidReportDescriptor[] definition:

#define MICROJOY_1_REPORT_ID 0x01

const uint8_t _hidReportDescriptor[] = {
	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x05,        // USAGE (Gamepad)
	0xa1, 0x01,        // COLLECTION (Application)
	0x85, MICROJOY_1_REPORT_ID,   //  REPORT ID (1)
	0x15, 0x00,        //   LOGICAL_MINIMUM (0) //Defining the buttons //10
	0x25, 0x01,        //   LOGICAL_MAXIMUM (1)
	0x35, 0x00,        //   PHYSICAL_MINIMUM (0)
	0x45, 0x01,        //   PHYSICAL_MAXIMUM (1)
	0x75, 0x01,        //    REPORT_SIZE (1)
	0x95, 0x0c,        //    REPORT_COUNT (12) //20
	0x05, 0x09,        //    USAGE_PAGE (Button)
	0x19, 0x01,        //    USAGE_MINIMUM (Button 1)
	0x29, 0x0c,        //    USAGE_MAXIMUM (Button 12)
	0x81, 0x02,        //    INPUT (Data,Var,Abs) // Send button data
	0x95, 0x04,        //    REPORT_COUNT (4) // Padding //30
	0x81, 0x01,        //    INPUT (Cnst,Ary,Abs) // Send padding
	0x05, 0x01,        //   USAGE_PAGE (Generic Desktop)
	0x26, 0xff, 0x03,  //   LOGICAL_MAXIMUM (255) // Analog stiiicks!
	0x46, 0xff, 0x03,  //   PHYSICAL_MAXIMUM (255) //61
	0x09, 0x30,        //   USAGE (X)
	0x09, 0x31,        //   USAGE (Y)
	0x09, 0x32,        //   USAGE (Z)
	0x09, 0x33,        //   USAGE (Rz)
	0x75, 0x10,        //   REPORT_SIZE (16) //71
	0x95, 0x04,        //   REPORT_COUNT (4)
	0x81, 0x02,        //   INPUT (Data,Var,Abs// Send data for our sticks
	0xc0
};

>>> TO HERE

extern const HIDDescriptor _hidInterface PROGMEM;

Hardware - Attach buttons to any of the pins 2-10 & 14-16
             to ground, and see different controller buttons
             be pressed.
            Analog inputs A0 - A3 are encoded using the full 10 bit resolution.      
  
  This code is in the public domain
//================================================================================

*/

#include <MicroJoy.h>


int flipPin = 0;
int led = 17;
MicroJoy microJoy;

void setup(){
  setupPins();
}

void loop(){
  // Always be getting fresh data
  dataForController_t controllerData = getControllerData();
  // Then send out the data over the USB connection
  microJoy.set(controllerData);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 16; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
//  pinMode(A4, INPUT);
//  digitalWrite(A4, HIGH);
//  pinMode(A5, INPUT);
//  digitalWrite(A5, HIGH);
  pinMode(led, OUTPUT);     
}



dataForController_t getControllerData(void){  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
//  controllerData.d2 = flipPin;
//  controllerData.d3 = flipPin;
  flipPin = flipPin xor 0x01;

/*
  controllerData.d2 = flipPin;
  controllerData.d3 = !flipPin;
  controllerData.d4 = flipPin;
  controllerData.d5 = !flipPin;
  controllerData.d6 = flipPin;
  controllerData.d7 = !flipPin;
  controllerData.d8 = flipPin;
  controllerData.d9 = !flipPin;
  controllerData.d10 = flipPin;
  controllerData.d14 = !flipPin;
  controllerData.d15 = flipPin;
  controllerData.d16 = !flipPin;
*/
  
  controllerData.d2 = !digitalRead(2);
  controllerData.d3 = !digitalRead(3);
  controllerData.d4 = !digitalRead(4);
  controllerData.d5 = !digitalRead(5);
  controllerData.d6 = !digitalRead(6);
  controllerData.d7 = !digitalRead(7);
  controllerData.d8 = !digitalRead(8);
  controllerData.d9 = !digitalRead(9);
  controllerData.d10 = !digitalRead(10);
  controllerData.d14 = !digitalRead(14);
  controllerData.d15 = !digitalRead(15);
  controllerData.d16 = !digitalRead(16);
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  


 /* use this to test instead of real input data
  controllerData.a0 =  random(1024);
  controllerData.a1 =  200;
  controllerData.a2 = 600;
  controllerData.a3 = 1024;
  digitalWrite(led, flipPin);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
*/
  
  controllerData.a0 =  analogRead(A0);
  controllerData.a1 = analogRead(A1);
  controllerData.a2 = analogRead(A2);
  controllerData.a3 = analogRead(A3);

  // And return the data!  
  return controllerData;
}
