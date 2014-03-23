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

#ifndef MicroJoy_h
#define MicroJoy_h

#include <inttypes.h>

// Prevent the joystick version of the hid descriptor in HID.cpp
// Report ID for our controller.  
#define MICROJOY_1_REPORT_ID 0x01

//  We need to make sure _hidReportDescriptor gets defined ahead
// of the one in HID.cpp which defines a Keyboard & Mouse device.


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

#include <Arduino.h>


//#ifndef 


// Car Controller - wasn't working
// 	0xC4	Accelerator
//	0xC5	Brake
//	0xC6	Clutch
//	0xC7	Shifter
//	0xC8	Steering
/* Not sure if an automobile simulator will be recognised by windows
	 0x05, 0x02,         //  Usage Page (Simulation Controls)
     0x09, 0x02,         //  Usage (Automobile)
     0xA1, 0x01,         //  Collection (Application)  <---- top level collection
     0x85, WPSCARCONTROLLER_1_REPORT_ID,   //  REPORT ID (3)
                         // ------------ Common global items ------------
     0x15, 0x00,         //    Log Min (0)
                         // ------------ Axises -------------------------
     0x09, 0x01,         //    Usage (Pointer)
     0xA1, 0x00,         //    Collection (Physical)
     0x09, 0xC4,         //      Usage (Accelerator)
     0x09, 0xC5,         //      Usage (Brake)
     0x09, 0xC6,         //      Usage (Clutch)
     0x09, 0xC8,         //      Usage (Steering)
     0x26, 0xFF, 0x03,   //      Log Max (1023)  <------ logical min (0) is carried over
     0x75, 0x10,         //      Report Size (16)
     0x95, 0x06,         //      Report Count (4)
     0x81, 0x02,         //      Input (Data, Variable, Absolute)
     0xC0,               //    End Collection

     0x05, 0x09,         //    Usage Page (Button)
     0x19, 0x01,         //    Usage Min (1)
     0x29, 0x0C,         //    Usage Max (12)
     0x25, 0x01,         //    Log Max (1)       <------ logical min (0) is carried over
     0x45, 0x00,         //    Phy Max (0)       <------ cancel physical min/max scaling
     0x65, 0x00,         //    Unit (None)       <------ cancel unit assignment
     0x75, 0x01,         //    Report Size (1)
     0x95, 0x0C,         //    Report Count (12)
     0x81, 0x02,         //    Input (Data, Variable, Absolute)
     0x75, 0x04,         //    Report Size (4)
     0x95, 0x01,         //    Report Count (1)
     0x81, 0x01,         //    Input (Cnst, Var, Abs)
     0xC0                //  End Collection
*/
/*
	 0x05, 0x01,         //  Usage Page (Generic Desktop)
     0x09, 0x05,         //  Usage (Gamepad)
     0xA1, 0x01,         //  Collection (Application)  <---- top level collection
     0x85, WPSCARCONTROLLER_1_REPORT_ID,   //  REPORT ID (1)
                         // ------------ Common global items ------------
     0x15, 0x00,         //    Log Min (0)
                         // ------------ Axises -------------------------
     0x09, 0x04,         //    Usage (Pointer) (Try 0x04 - Joy & 0x08 - Multi Axis
     0xA1, 0x00,         //    Collection (Physical)
     0x19, 0x30,         //      Usage Min (Accelerator)
     0x29, 0x33,         //      Usage Max (Wheel)
     0x26, 0xFF, 0x00,   //      Log Max (1023)  <------ logical min (0) is carried over
     0x75, 0x08,         //      Report Size (16)
     0x95, 0x04,         //      Report Count (4)
     0x81, 0x02,         //      Input (Data, Variable, Absolute)
//    0xC0,               //    End Collection

     0x05, 0x09,         //    Usage Page (Button)
     0x19, 0x01,         //    Usage Min (1)
     0x29, 0x0C,         //    Usage Max (12)
     0x25, 0x01,         //    Log Max (1)       <------ logical min (0) is carried over
     0x45, 0x00,         //    Phy Max (0)       <------ cancel physical min/max scaling
     0x65, 0x00,         //    Unit (None)       <------ cancel unit assignment
     0x75, 0x01,         //    Report Size (1)
     0x95, 0x0C,         //    Report Count (12)
     0x81, 0x02,         //    Input (Data, Variable, Absolute)
     0x75, 0x04,         //    Report Size (4)
     0x95, 0x01,         //    Report Count (1)
     0x81, 0x01,         //    Input (Cnst, Var, Abs)
     0xC0,                //  End Collection
     0xC0                //  End Collection
*/
//};


//	ProMicro

#ifndef HID_REPORT_DESCRIPTOR

typedef struct dataForController_t
{
    uint8_t d2 : 1;    // For the buttons, 
    uint8_t d3 : 1;     //  0 is off
    uint8_t d4 : 1;        //  1 is on
    uint8_t d5 : 1;        
    uint8_t d6 : 1;        // The : 1 here just tells the compiler
    uint8_t d7 : 1;        //  to only have 1 bit for each variable.
                             //  This saves a lot of space for our type!
    uint8_t d8 : 1;
    uint8_t d9 : 1;
    uint8_t d10 : 1;
    uint8_t d14 : 1;
    uint8_t d15 : 1;
    uint8_t d16 : 1;  // Each of these member variables
                             
    uint16_t a0 : 16;  // Each of the analog stick values can range from 0 to 1023
    uint16_t a1 : 16;  //  0 is fully left or up
    uint16_t a2 : 16; //  1023 is fully right or down 
    uint16_t a3 : 16; //  512 is centered.
    
} dataForController_t;

dataForController_t getBlankDataForController(void);

typedef struct {
	// digital buttons, 0 = off, 1 = on
	uint8_t d2 : 1;
	uint8_t d3 : 1;
	uint8_t d4 : 1;
	uint8_t d5 : 1;
	uint8_t d6 : 1;
	uint8_t d7 : 1;   //End first button byte
	uint8_t d8 : 1; // Start second button byte
	uint8_t d9 : 1;
	uint8_t d10 : 1;
	uint8_t d14 : 1;
	uint8_t d15 : 1;
	uint8_t d16 : 1;
	uint8_t : 4; //padding to finish off second button byte
	// digital direction, use the dir_* constants(enum)
	// 8 = center, 0 = up, 1 = up/right, 2 = right, 3 = right/down
	// 4 = down, 5 = down/left, 6 = left, 7 = left/up
//	uint8_t direction;
	// left and right analog sticks, 0x00 left/up, 0x80 middle, 0xff right/down
	uint16_t a0;
	uint16_t a1;
	uint16_t a2;
	uint16_t a3;
} JoystickReport;

class MicroJoy
{
private:
	JoystickReport _joystickReport;
    void sendReport(JoystickReport* joyReport);
public:
	MicroJoy();
	void begin();
	void end();
    void set(dataForController_t);
    dataForController_t get();
};

// extern MicroJoy_ MicroJoy;

#endif
#endif