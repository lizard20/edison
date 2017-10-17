/*
** Program: digital_input.c
** Description: Read a digital input and display its value
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <mraa.h>

const int PORT = 5;

int 
main ( void )
{
    /* declare variable as a gpio type */
	mraa_gpio_context port_input;

    /* initialize variable with a port number*/
    port_input = mraa_gpio_init ( PORT );

    /* set gpio direction to input */
	mraa_gpio_dir ( port_input, MRAA_GPIO_IN );

    /* read port value */
	int value = mraa_gpio_read ( port_input );

    /* print port number and its value */
	printf ( "Input port %d: %d\n", PORT, value );

    /* close port */
	mraa_gpio_close ( port_input );

	return ( MRAA_SUCCESS );
}
