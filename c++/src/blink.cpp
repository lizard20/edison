// Program: blink.cpp
// Description: blink LED
// Author: Aldo Nunez

#include <mraa.hpp>

enum STATE { OFF, ON }; 		// OFF = 0, ON = 1
const int LED ( 13 ); 			// 13 ~ led DS2
const useconds_t T ( 1e6 );		// 1e6 ~ 1 sec	

int
main ( void )
{
	// create and initialize gpio pin
	mraa::Gpio led ( LED ); 					
	// set gpio direction to out
	mraa::Result response = led.dir ( mraa::DIR_OUT );

	while ( true )				// blink indefinitely until (Ctrl + c)
	{
		led.write ( ON );		// turn on led
		usleep ( T ); 			// wait for 1 second
		led.write ( OFF );		// turn off led
		usleep ( T );			// wait for 1 second
	}
	
	return ( MRAA_SUCCESS );	// exit
}

