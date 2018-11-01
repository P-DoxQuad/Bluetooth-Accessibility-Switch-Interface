/*
Name:     button.h
Created:  04/15/2017 1:05:00 PM
Updated:  09/26/2017 11:38:00 PM
Author:   Michael Dzura
Version: 2.6

Declaration of variables and functions
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

/*********** INPUTS ***********/
#define INPUT_SWITCH	 10	   // Input Pin On Feather 32u4.
/******************************/

/******** TIME VARIANTS *******/
#define CLICK_TIME		 2000   // The Time Of A Single Switch Click. Only Adjust This. Will Multiply By 2.
/******************************/

/****** SWITCH LOGIC **********/
int lastSwitchState;		   // The Previous Reading From The Input Pin.
int pressTrigger;			   // Flag For Switch Press.
int switchState;			   // Value Of The Switch State.
long pressedTime;			   // Timestamp For When The Switch Is Pressed.
long releasedTime;			   // Timestamp For When The Switch Is Released.
long pressDuration;			   // Total Duration The Switch Was Pressed.
/******************************/

/********** DEBOUNCE **********/
#define DEBOUNCEDELAY	 10	   // Debounce Filter Time
long lastDebounceTime;		   // Previous Debounce Timestamp
/******************************/


int button(int input_pin, long short_Click);

#endif
