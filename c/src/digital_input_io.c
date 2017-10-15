/*
** Program: digital_input_io.c
** Description: Read one of the digital input ports
                between  0 and 13 and displays
                its value
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <mraa.h>

#define VERSION 0.1

typedef enum { false, true } bool;

/* Number of digital input ports*/
const unsigned int PORTS = 13;

/*
** Name:        isValid
** Parameters:  string input
** Output:      Boolean
                true - if the input is an integer number.
**              false - if the input is not an integer number
** Description: Check if the input is an integer number
*/
bool isValid ( char* );


int
main ( int argc, char* argv[] )
{
	if ( argc < 2 )
	{
		printf ( "Usage: %s <port> \n", argv [ 0 ]);
        printf ( "<port>: 0 | 1 | 2 | 3 | 4 | 5 |.....| 13 \n" );
		return 1;
	}

    /* Check if the argument is a number */
    if ( !isValid ( argv [ 1 ] ) )
    {
        printf ( "<port> must be an integer number between: 0 - 13 \n" );

        return 1;
    }

    int input_port =  atoi ( argv [ 1 ] );

    /* Check if the number is between: 0 - 13 */
    if ( ( input_port < 0 ) || ( input_port  > PORTS ) )
    {
        printf ( "<port> must be an integer number between: 0 - 13 \n" );

        return 1;
    }

    mraa_gpio_context pin_input;

    pin_input = mraa_gpio_init ( input_port );
    if ( pin_input == NULL )
    {
        fprintf ( stderr, "The port %d that you requested is not valid!", pin_input );
        exit ( 1 );
    }

    /* set gpio drection to  out */
    mraa_result_t response = mraa_gpio_dir ( pin_input, MRAA_GPIO_IN );
    if ( response != MRAA_SUCCESS )
    {
        mraa_result_print ( response );
    }

    /* read input port */
    int value = mraa_gpio_read ( pin_input );
    if ( value == -1 )
    {
        fprintf (stderr, "Failed reading port %d", pin_input );
        exit ( 1 );
    }

    printf ( "MRAA Version: %s\n", mraa_get_version () );
    printf ( "Platform: %s\n", mraa_get_platform_name () );
    printf ( "Input port %d: %d\n", input_port, value );

    mraa_gpio_close ( pin_input );

    return ( MRAA_SUCCESS );


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
