// Program: blink.cpp
// Description: blink LED
// Author: Aldo Nunez
#include <mraa.hpp>

int
main ( void )
{
	// create and initialize gpio pin
	mraa::Gpio led ( 13 );

	// set gpio direction to out
	mraa::Result response = led.dir ( mraa::DIR_OUT );

	// blink indefinitely until Ctrl + c
	while ( true )
	{
		// turn on led
		led.write ( 1 );
		// wait for 1 second
		sleep ( 1 );
		// turn off led
		led.write ( 0 );
		// wait for 1 second
		usleep ( 1 );
	}

	// exit
	return ( MRAA_SUCCESS );
}

