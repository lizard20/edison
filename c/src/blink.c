/*
** Program: blink.c
** Description: blink LED DS2
** Author: Aldo Nunez
*/

#include <mraa.h>

int main ( void )
{
	/* declare led  variable as a gpio type */
	mraa_gpio_context led;

	/* initialize led with a pin number*/
	led = mraa_gpio_init ( 13 );

	/* set gpio direction to out */
	mraa_gpio_dir ( led, MRAA_GPIO_OUT );

	/* blink indefinitely until (Ctrl + c) */
	while ( 1 )
	{
		/* turn on led */
		mraa_gpio_write ( led, 1 );
		/* wait for 1 second */
		sleep ( 1 );
		/* turn off  led */
		mraa_gpio_write ( led, 0 );
		/* wait for 1 second */
		sleep ( 1 );
	}
	/* close the gpio context */
	mraa_gpio_close ( led );

	return ( MRAA_SUCCESS );
}
