//================================================================================
//	WPS CAR CONTROLLER
//  Ver 0.1 (c) Jon Lidgard 08/03/2014
//================================================================================


//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <inttypes.h>
//#include "Arduino.h"
//#include "wiring_private.h"

//#include <USBAPI.h>

#include "MicroJoy.h"

void MicroJoy::begin(void) 
{
}

void MicroJoy	::end(void) 
{
}

void MicroJoy::set(dataForController_t controllerData)
{
    _joystickReport.d2 = controllerData.d2;
    _joystickReport.d3 = controllerData.d3;
    _joystickReport.d4 = controllerData.d4;
    _joystickReport.d5 = controllerData.d5;
    _joystickReport.d6 = controllerData.d6;
    _joystickReport.d7 = controllerData.d7;
    _joystickReport.d8 = controllerData.d8;
    _joystickReport.d9 = controllerData.d9;
    _joystickReport.d10 = controllerData.d10;
    _joystickReport.d14 = controllerData.d14;
    _joystickReport.d15 = controllerData.d15;
    _joystickReport.d16 = controllerData.d16;

    _joystickReport.a0 = controllerData.a0;
    _joystickReport.a1 = controllerData.a1;
    _joystickReport.a2 = controllerData.a2;
    _joystickReport.a3 = controllerData.a3;

    // And send the data out!
    sendReport(&_joystickReport);
}

void MicroJoy::sendReport(JoystickReport* joyReport)
{
	HID_SendReport(MICROJOY_1_REPORT_ID,joyReport,sizeof(JoystickReport));
}

dataForController_t MicroJoy::get(void){
    dataForController_t controllerData;

    // Set everything to reflect the current state
    controllerData.d2 = _joystickReport.d2;
    controllerData.d3 = _joystickReport.d3;
    controllerData.d4 = _joystickReport.d4;
    controllerData.d5 = _joystickReport.d5;
    controllerData.d6 = _joystickReport.d6;
    controllerData.d7 = _joystickReport.d7;
    controllerData.d8 = _joystickReport.d8;
    controllerData.d9 = _joystickReport.d9;
    controllerData.d10 = _joystickReport.d10;
    controllerData.d14 = _joystickReport.d14;
    controllerData.d15 = _joystickReport.d15;
    controllerData.d16 = _joystickReport.d16;

    controllerData.a0 = _joystickReport.a0;
    controllerData.a1 = _joystickReport.a1;
    controllerData.a2 = _joystickReport.a2;
    controllerData.a3 = _joystickReport.a3;
    return controllerData;
}

dataForController_t getBlankDataForController(void){
    // Create a dataForController_t
    dataForController_t controllerData;
    // Make the buttons zero
    controllerData.d2 = 0;
    controllerData.d3 = 0;
    controllerData.d4 = 0;
    controllerData.d5 = 0;
    controllerData.d6 = 0;
    controllerData.d7 = 0;
    controllerData.d8 = 0;
    controllerData.d9 = 0;
    controllerData.d10 = 0;
    controllerData.d14 = 0;
    controllerData.d15 = 0;
    controllerData.d16 = 0;

    controllerData.a0 = 0;
    controllerData.a1 = 0;
    controllerData.a2 = 0;
    controllerData.a3 = 0;
    // And return the data!
    return controllerData;
}

MicroJoy::MicroJoy(void) 
{
    set(getBlankDataForController());
}

//	Singleton for MicroJoy

//MicroJoy_ MicroJoy;
