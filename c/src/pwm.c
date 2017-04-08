/*
** Name: pwm.c
** Description: Generates a PWM output. The user enters
**				the percentage of  duty cycle
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <mraa.h>

typedef enum{ false, true } bool;
enum PWM { PWM0 = 3, PWM1 = 5, PWM2 = 6, PWM3 = 9 } pwm_port;
const int T =  20000; 		/* T ~ period in usec */

/*
** Name: 		isValid
** Parameters:  pointer to string
** Output: 		Boolean, true - if it is a valid input.
**				false - if it is not a valid input
** Description:	Check if the input is a number or a
** 				decimal point.
*/
bool isValid ( char* );

int
main ( int argc, char* argv [] )
{
	/* checks if the number of arguments is valid */
	if ( argc < 2 )
	{
		printf ( "Usage: %s <duty cycle>\n", argv [ 0 ] );
		printf ( "<duty cycle> 0.0 ... 100.0\n" );
		return 1;
	}

	/* checks if the argument is  a valid  number */
	if ( !isValid ( argv [ 1 ] ) )
	{
		printf ( "Invalid argument....\n" );
		printf ( "<duty cycle> must be a number between: 0.0 - 100.0 \n" );

		return 1;
	}

	/*	converts the input argument to floating point
		and checks if it is in the valid interval
	*/
	float duty_cycle =  atof ( argv [ 1 ] );		/* percentage value */
	if ( ( duty_cycle > 100.0 ) || ( duty_cycle  < 0.0 ) )
	{
		printf ( "<duty cycle> must be between: 0.0 and 100.0\n" );
		return 1;
	}

	pwm_port = PWM0;
	mraa_init ();
	mraa_pwm_context pwm;
	pwm = mraa_pwm_init ( pwm_port );

	if ( pwm == NULL )
	{
        return 1;
	}

	mraa_pwm_enable ( pwm, true );
	mraa_pwm_period_us ( pwm, T );
	mraa_pwm_write ( pwm, duty_cycle / 100.0 );

	printf ( "MRAA Version: %s\n", mraa_get_version () );
	printf ( "Platform: %s\n", mraa_get_platform_name () );
	printf ( "Port Number: %d\n", pwm_port );
	printf ( "Period: %1.3f sec \n", T * 1e-6 );
	printf ( "Frequency: %2.2f Hz \n", 1e6 / T );
	printf ( "Percentage of PWM: %2.1f \n",  100 * mraa_pwm_read ( pwm ) );
	printf ( "Press \"Enter\" to finish.\n" );

	getchar ();
	mraa_pwm_close ( pwm );

	return ( MRAA_SUCCESS );
}

bool
isValid ( char* str )
{
	while ( *str != 0 )
	{
		if ( !isdigit ( *str )  &&  ( *str != '.' ) )
		{
			return false;
		}
		str++;
	}
	return true;
}
