/* Program: blink.c
** Description: blink LED
** Author: Aldo Nunez
*/

#include <mraa.h>

enum STATE { OFF, ON };		// OFF = 0, ON = 1
const int LED_PIN = 13;		// 13 ~ led DS2
const useconds_t T = 1e6;	// 1e6 ~ 1 sec

int
main ( void )
{
	mraa_init (); 							// initialize mraa 
	mraa_gpio_context led;					// create access to gpio  pin
	led = mraa_gpio_init ( LED_PIN );	
	mraa_gpio_dir ( led, MRAA_GPIO_OUT ); 	// set gpio direction to out
	
	while ( 1 )								// blink indefinitely until (Ctrl + c)
	{
		mraa_gpio_write ( led, ON );		// turn on led
		usleep ( T );					 	// wait for 1 second
		mraa_gpio_write ( led, OFF );		// turn off  led
		usleep ( T );						// wait for 1 second
	}

	mraa_gpio_close ( led );				// close and exit

	return ( MRAA_SUCCESS );
}
