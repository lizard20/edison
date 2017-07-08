/*
** Program: blink_io.c
** Description: blink any LED connected to ports
				IO0 to IO13
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <signal.h>
#include <mraa.h>

/* false = 0, true = 1 */
typedef enum { false, true } bool;

/* OFF = 0, ON = 1 */
enum STATE { OFF, ON };

/* number of digital outputs ports */
const unsigned int PORTS = 14;

/* 1e6 ~ 1 sec */
const useconds_t T = 1e6;

volatile sig_atomic_t  flag = 1;

/*
** Name:        isValid
** Parameters:  string input
** Output:      Boolean
                true - if the input is an integer number.
**              false - if the input is not an integer number
** Description: Check if the input is an integer number
*/
bool isValid ( char* );

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
main ( int argc, char* argv [] )
{
	if ( argc < 2 )
	{
		fprintf ( stderr, "Usage: %s <port> \n", argv [ 0 ] );
        fprintf ( stderr, "<port>: 0 | 1 | 2 | 3 | 4 | 5 |.....| 13 \n" );

		return 1;
	}
	/* Check if the argument is a number */
    if ( !isValid ( argv [ 1 ] ) )
    {
        fprintf ( stderr, "<port> must be an integer number between: 0 - 13 \n" );

        return 1;
    }

	int port =  atoi ( argv [ 1 ] );

    /* Check if the number is between: 0 - 13 */
    if ( ( port < 0 ) || ( port  > PORTS - 1 ) )
    {
        fprintf ( stderr, "<port> must be an integer number between: 0 - 13 \n" );

        return 1;
    }

	/* create access to gpio  pin */
	mraa_gpio_context led;

	/* Initialize pin LED_PIN for led */
	led = mraa_gpio_init ( port );
	if ( led == NULL )
	{
        fprintf (stderr, "The port %d that you requested is not valid!", port );
        return 1;
    }

	/* set gpio drection to  out */
    mraa_result_t response = mraa_gpio_dir ( led, MRAA_GPIO_OUT );
    if ( response != MRAA_SUCCESS )
    {
        mraa_result_print ( response );
    }

    printf ( "MRAA Version: %s\n", mraa_get_version () );
    printf ( "Platform: %s\n", mraa_get_platform_name () );
    printf ( "blinking port %d...\n", port );
	printf ( "To finish press: Ctrl + c \n" );

	signal ( SIGINT, manage_signal );

	/* blink indefinitely until (Ctrl + c) */
	while ( flag )
	{
		response = mraa_gpio_write ( led, ON );
        if ( response != MRAA_SUCCESS )
        {
         	mraa_result_print ( response );
        }

        usleep ( T );

        response = mraa_gpio_write ( led, OFF );
        if ( response != MRAA_SUCCESS )
        {
            mraa_result_print ( response );
        }

		usleep ( T );
	}

	mraa_gpio_close ( led );

	return 0;
}

bool
isValid ( char* str )
{
    while ( *str != 0 )
    {
        if ( !isdigit ( *str ) )
        {
            return false;
        }
        str++;
    }
    return true;
}

void
manage_signal ( int sig )
{
	if ( sig == SIGINT )
	{
		flag = 0;
	}
	printf ("\nprogram is closing ... \n" );

	return;
}
