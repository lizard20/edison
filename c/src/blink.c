/* 
** Program: blink.c
** Description: blink LED
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <signal.h>
#include <mraa.h>

enum STATE { OFF, ON };		/* OFF = 0, ON = 1 */
const int LED_PIN = 13;		/* 13 ~ led DS2 */
const useconds_t T = 1e6;	/* 1e6 ~ 1 sec */

volatile sig_atomic_t  flag = 1;

/*
** Name: manage_signal
** Input: Integer
** Output: None
** Description: Catch the signal interrupt, 
** 				'Ctrl + c' signal  generated
** 				by the user  and  modify 
** 				flag variable
*/
void manage_signal ( int );

int
main ()
{

	mraa_init (); 							/* initialize mraa */
	mraa_gpio_context led;					/* create access to gpio  pin */
	led = mraa_gpio_init ( LED_PIN );	    /* Initialize pin LED_PIN for led */
	mraa_gpio_dir ( led, MRAA_GPIO_OUT ); 	/* set gpio direction to out */

	printf ( "To finish press: Ctrl + c \n" );

	signal ( SIGINT, manage_signal );
	
	while ( flag )							/* blink indefinitely until (Ctrl + c) */
	{
		mraa_gpio_write ( led, ON );		/* turn on led */
		usleep ( T );					 	/* wait for 1 second */
		mraa_gpio_write ( led, OFF );		/* turn off  led */
		usleep ( T );						/* wait for 1 second */
	}

	mraa_gpio_close ( led );

	return 0;
}

void
manage_signal ( int sig )
{
	if ( sig == SIGINT )	
	{
		flag = 0;
	}
	printf ("\n blink is closing ... \n" );

	return;
}


