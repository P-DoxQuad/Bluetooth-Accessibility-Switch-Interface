/*
Name:     TimeWait.c
Created:  04/15/2017 1:35:00 PM
Author:   Michael Dzura
Version: 1.0

Definition Of TimeWait Function. Creates A Simple Looping 
Pause Based On The Time Parameter Given. This Is To Replace
Arduino Built-in Delay. Use This Library With Any Project 
That Needs Some Kind Of A Delay. This Will Make Your Code  
Less Arduino Dependent.


*/

#include "Arduino.h" // Needs to include Arduino Library. Only Needed When Not Main File.
#include "TimeWait.h" // Includes Variable And Function Declarations.


/************************** Wait Function *******************************
 * Independent Function That Waits In Loop For Defined Interval.		*
 * Similar To Arduino Built-in Delay Function, But Non-Specific.		*
 ************************************************************************/
void wait(long interval) {
	unsigned long current = 0, previous = 0;
	current = previous = millis();

	// Counts the delay in Milliseconds, and checks for input
	// signal from switch:
	while((current-previous) < interval) {
		current = millis();

		//Serial.println(current-previous);

	}
}
