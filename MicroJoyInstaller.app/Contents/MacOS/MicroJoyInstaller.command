#!/bin/sh
# MicroJoy install script for OSX, written by Jon Lidgard 2014
echo
echo
echo "Installing MicroJoy..."
echo 


#Get to the current directory of the .app
APP_DIR="$(dirname "$0")"
cd "$APP_DIR"

# Get back to the directory that holds the .app bundle
cd ../../..
BUNDLE_DIR=`pwd`

#Make sure the Arduino app exists...
if [ -e "Arduino.app" ] ; then
    # And make sure it's run at least once, so we have a preferences file
    if [ -e "$HOME/Library/Arduino/preferences.txt" ] ; then
		echo "Found Arduino, installing MicroJoy"
    	echo
    else
    	echo "Please run Arduino, quit & then try again to install MicroJoy"
    	exit
    fi
else
    echo "Couldn't find Arduino.app... You must run the installer from the same folder as Arduino.app"
    pwd
    exit
fi


ARDUINO_DIR="$BUNDLE_DIR/Arduino.app/Contents/Resources/Java/"


# Start copying files


# Append the ProMicro files to the boards.txt file

# Add the Sparkfun ProMicro definition files & bootloader
# Test if ProMicro has already been added to boards.txt

cd "$ARDUINO_DIR/hardware/arduino"

grep promicro boards.txt
if [ $? -eq 0 ] ; then
    echo "Sparkfun ProMicro SF32u4 files already installed, skipping..."
else
    # Prepare the SF32u4 files for a merge
    mkdir -p "$APP_DIR/hardware/arduino"
    cp -R "$APP_DIR/SF32u4/" "$APP_DIR/hardware/arduino/"
    mv "$APP_DIR/hardware/arduino/boards.txt" "$APP_DIR/hardware/arduino/promicro_boards.txt"
    cp -R "$APP_DIR/hardware" "$ARDUINO_DIR"
    rm -R "$APP_DIR/hardware"
	
    cat boards.txt promicro_boards.txt > temp.txt
    yes | cp temp.txt boards.txt
    rm temp.txt
    rm promicro_boards.txt
    echo "Sparkfun ProMicro SF32u4 files installed."
fi


# Add the MicroJoy board definition files
# Test if MicroJoy has already been added to boards.txt

grep microjoy boards.txt
if [ $? -eq 0 ] ; then
    echo "MicroJoy definition already installed, skipping..."
else
    cp "$APP_DIR/MicroJoy/microjoy_boards.txt" "$ARDUINO_DIR/hardware/arduino"
    cat boards.txt microjoy_boards.txt > temp.txt
    yes | cp temp.txt boards.txt
    rm temp.txt
    rm microjoy_boards.txt
    echo "MicroJoy board definition files installed."
fi


# Now make the changes to HID.cpp in the microjoy directory

cp -R "cores/arduino" "cores/microjoy"
cd "cores/microjoy"

if [ -e HID.cpp ] ; then

grep MICROJOY HID.cpp
if [ $? -eq 0 ] ; then
    echo "HID.cpp already patched...skipping."
else
    echo "Patching HID.cpp to optionally use Joystick HID Descriptor in MicroJoy.h"
    patch "HID.cpp" "$APP_DIR/MicroJoy/HID.patch"
fi
else 
    echo "HID.cpp not found...cannot patch!"
fi


# Now make the changes to USBCore.cpp - not vital, just changes Manufacturer & Product descriptions

if [ -e USBCore.cpp ] ; then

grep "'M','i','c','r','o','J','o','y'" USBCore.cpp
if [ $? -eq 0 ] ; then
    echo "USBCore.cpp already patched...skipping."
else
    echo "Patching USBCore.cpp to change Manufacturer & Product descriptions"
    patch "USBCore.cpp" "$APP_DIR/MicroJoy/USBCore.patch"
fi
else 
    echo "USBCore.cpp not found...cannot patch!"
fi


# Add the MicroJoy library

SKETCHBOOK_PATH=`grep sketchbook.path "$HOME/Library/Arduino/preferences.txt" | cut -d= -f2`
if [ -d "$SKETCHBOOK_PATH"  ] ; then
   echo "SketchPath=$SKETCHBOOK_PATH"
   cp -R "$APP_DIR/MicroJoy/libraries" "$SKETCHBOOK_PATH/"
fi

# All done

echo
echo
echo "MicroJoy merge is complete."
echo
echo
