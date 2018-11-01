/*
Name:     32u4-BLE_Switch-v1.ino
Created:  09/04/2016 10:25:00 PM
Author:   Michael Dzura
Version:  1.0

**FOR USE WITH ADAFRUIT FEATHER 32u4 BLE MICROCONTROLLER**

Input (Pin 10 - 3.5mm Mono Jack).
Output (Pin 9 - Yellow LED).

The implementation of this code is for a Wireless Bluetooth
Switch. The Switch can send 3 commands to a device (ie. iOS 7+, Android 5.0+)
activated by 3 timed button gestures - Short Press, Long Press, 
Longest Press. **See button.c for time calculation implementation.


**Notes:
Over BLE, Keyboard Scan Codes compliant with HID are sent to the
device. Each scan code acts like a keypress followed by a release.

<Release> 00-00
<Spacebar> 00-00-2C-00-00
<Ctrl-Alt-RightArw> 05-00-4F-00-00
<Ctrl-Alt-LeftArw> 05-00-50-00-00

When flashing MCU, unpair, and forget Bluefruit from iOS. For some reason in iOS 9 onward
the Bluefruit will fail to send commands, despite having a connection status. To fix
this, unpair and forget Bluefruit from iOS, and reboot iOS.



*/

//#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_ATParser.h>
#include "BluefruitConfig.h"
//#include <SPI.h>

#include "button.h"
#include "button.c"
#include "TimeWait.h"
#include "TimeWait.c"

/********** OUTPUTS ***********/
int LED[3] = {13,9,10};			 
//int RELAY[3] = {3,4,5};
/******************************/

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.5"
#define BLE_ENABLED 1

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

int initialize_ble();
void getUserInput(char buffer[], uint8_t maxSize);


void setup() {
	Serial.begin(115200);

	pinMode(INPUT_SWITCH, INPUT_PULLUP);

  for (int i = 0; i <= 2; i++) {
	pinMode(LED[i], OUTPUT);
	//pinMode(RELAY[i], OUTPUT);
  }

  digitalWrite(LED[1], HIGH);
  wait(500);
  digitalWrite(LED[1], LOW);
  Serial.println("READY!!");

	if (BLE_ENABLED == true) {
		if (initialize_ble() == true) {							// Start BLE and relevant services.
			Serial.println("\nBLUETOOTH CONNECTIVITY IS AVAILABLE!");
		} else {
			Serial.println("\nBLUETOOTH CONNECTIVITY IS UNAVAILABLE!");
		}
	}
}

void loop() {
		int state = button(INPUT_SWITCH, CLICK_TIME);			// Calls the button function and returns value of 1-3

		// Activated On Short Click.
		if (state == 1) {
			Serial.println("Short Press!");
			ble.println("AT+BleKeyboardcode=00-00-2C-00-00");	// Send <Spacebar>
			digitalWrite(LED[1], HIGH);				
			wait(150);
			ble.println("AT+BleKeyboardcode=00-00");			// Send <Release>
			digitalWrite(LED[1], LOW);
			
		// Activated On Long Click.
		} else if (state == 2) {
			Serial.println("Long Press!");
			ble.println("AT+BleKeyboardcode=05-00-4F-00-00");	// Send <Ctrl-Alt-RightArw>
			for (int i = 0; i < state; i++) {
				digitalWrite(LED[1], HIGH);				
				wait(125);				
				digitalWrite(LED[1], LOW);
				wait(125);
			}	
			ble.println("AT+BleKeyboardcode=00-00");			// Send <Release>

		// Activated On Longest Click.
		} else if (state == 3) {
			Serial.println("Longest Press!");
			ble.println("AT+BleKeyboardcode=05-00-50-00-00");	// Send <Ctrl-Alt-LeftArw>
			for (int i = 0; i < state; i++) {				
				digitalWrite(LED[1], HIGH);
				wait(125);				
				digitalWrite(LED[1], LOW);
				wait(125);
			}
			ble.println("AT+BleKeyboardcode=00-00");			// Send <Release>
		} 
}

/**************************************************************************
 * Start Broadcasting BLE Radio and Enable HID Keyboard Service			  *
***************************************************************************/
int initialize_ble() {
	if (!ble.begin(VERBOSE_MODE)) {
		Serial.println("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
	} else {
		Serial.println(F("OK!"));
	}

	/* Print Bluefruit information */
	Serial.println("Requesting Bluefruit info:");
	ble.info();

	/* Perform a factory reset to make sure everything is in a known state */
	if (FACTORYRESET_ENABLE) {
		
		Serial.println(F("Performing a factory reset: "));
		if (!ble.factoryReset()) {
			Serial.println("Couldn't Factory Reset");
		} else {
			Serial.println(F("OK!"));
		}
	}


	/****************************************************
	 * Sets the broadcast name. What is displayed as a	*
	 * searchable device.								*
	 ****************************************************/
	if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=BLE_Sw01"))) {
		Serial.println("Could Not Set Device Name");
	}


	/*****************************************************
	 * Enable HID Service. HID is the protocol compliance *
	 * for all input peripherals like Keyboards, Mice,	  *
	 * Gamepads.									      *
	 ******************************************************/
	Serial.println(F("\nEnable HID Service (including Keyboard): "));
	if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION)) {          // Checks BLE Firmware
		if (!ble.sendCommandCheckOK(F("\nAT+BleHIDEn=On"))) {      // Was BLE HID Enabled Successfuly
			Serial.println("Could Not Enable HID");
			return 0;
		}
	} else {
		if (!ble.sendCommandCheckOK(F("\nAT+BleKeyboardEn=On"))) { // Was Keyboard Enabled Successfully
			Serial.println("Could Not Enable Keyboard");
			return 0;
		}
	}
	return 1;
}

/**************************************************************************/
/*!
    Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
void getUserInput(char buffer[], uint8_t maxSize)
{
  memset(buffer, 0, maxSize);
  while( Serial.available() == 0 ) {
    delay(1);
  }

  uint8_t count=0;

  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.available() == 0) );
}