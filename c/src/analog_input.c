/*
** Program: analog_input.c
** Description: Reads analog input and displays its value
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <mraa.h>

typedef enum { false, true } bool;

/*
** Name: 		isValid
** Parameters:  pointer to string
** Output: 		Boolean, true - if it is a valid input. 	
**				false - if it is not a valid input
** Description:	Check if the input is an integer number
*/
bool isValid ( char* );

enum ANALOG { A0, A1, A2, A3, A4, A5 } analog_input;	/* analog ports: A0 - A5 */
const int NBITS  = 12 ;			/* number of bits */

int
main ( int argc, char* argv[] )
{
	if ( argc < 2 )
	{
		printf ( "Usage: %s <port>\n", argv [ 0 ] );  
		printf ( "<port>: 0..5\n" );  

		return 1;
	}

	if ( !isValid ( argv [ 1 ] ) )
	{
		printf ( "<port> must be between: 0..5\n" );
		return 1;	
	}
	
	float port =  atof ( argv [ 1 ] );
	
	if ( ( port < A0 ) || ( port  > A5 ) )
	{
		printf ( "<port> must be between: 0..5\n" );
		return 1;
	}


	uint16_t int_value = 0;	/* variable  to read integer value */
	float float_value = 0.0;	/* variable to read float value */
	analog_input = port;

	mraa_init ();
	mraa_aio_context ( adc_port );
	adc_port = mraa_aio_init ( analog_input );

	if ( adc_port == NULL )
	{
        return 1;
    }

	mraa_aio_set_bit ( adc_port, NBITS ); /* Configure ADC */

	printf ( "MRAA Version: %s\n", mraa_get_version () );
	printf ( "Platform: %s\n", mraa_get_platform_name () );

	while ( 1 )
	{
		int_value = mraa_aio_read ( adc_port );	/* reading integer value */
		float_value = mraa_aio_read_float ( adc_port );	/* reading float value */
        printf ( "ADC %d read integer: %d\n", analog_input, int_value );
        printf ( "ADC %d read float: %f\n", analog_input, float_value );
		sleep ( 1 );
    }

	mraa_aoi_close ( adc_port );
	return ( MRAA_SUCCESS );
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


