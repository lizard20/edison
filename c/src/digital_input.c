// Program: digital_input.c
// Description: Read digital input and display its value
// Author: Aldo Nunez

#include <stdio.h>
#include <mraa.h>

const int PIN_INPUT = 5;

int
main ( void )
{
	mraa_init ();
	mraa_gpio_context pin_input;
	pin_input = mraa_gpio_init ( PIN_INPUT );
	mraa_gpio_dir ( pin_input, MRAA_GPIO_IN );

	int value = mraa_gpio_read ( pin_input );

	printf ( "MRAA Version: %s\n", mraa_get_version () );
	printf ( "Platform: %s\n", mraa_get_platform_name () );
	printf ( "Input pin_%d: %d\n", PIN_INPUT, value );

	mraa_gpio_close ( pin_input );

	return ( MRAA_SUCCESS );
}
