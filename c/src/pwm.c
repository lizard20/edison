/* Name: pwm.c
** Description: Generates a PWM output. The user enters
** 				the port name  and the percentage of duty cycle
** Author: Aldo Nunez
*/

#
#include <stdio.h>
#include <string.h>
#include <mraa.h>

typedef enum { false, true } bool;

const int pwm_num [] = { 3, 5, 6, 9 };
const char* pwm [] = { "P0", "P1", "P2", "P3" };
const int T =  20000; 		/* T ~ period in usec */

/************  Functions prototypes ************/
/*
** Name:      	isValidArgument
** Parameters:  1.- Integer,  number of arguments
** 				2.- Initial address of  pointers array to char
** Output:      Boolean
                true -  if the first parameter is a valid port:
						P0, P1, P2, P3
						if the second parameter is a valid 
						Duty Cycle percentage: 0% - 100%
**              false - if it is not a valid Port.
**              		if it is not a valid Duty Cycle
** Description: Check if the inputs are valid arguments
*/
bool isValidArgument ( int , char* [] );

/*
** Name: 		isValidPort
** Parameters:  Pointer to a character
** Output: 		Integer:
** 					Port index number
**	 				-1 if it is not a valid port
** Description:	Check if the input is a valid port. 
** 				If it is a valid port,  return port indez number
** 				If it is not a vali port, return -1
*/
int isValidPort ( char* );

/*
** Name: 		isValidDC
** Parameters:  Pointer to a character
** Output: 		Boolean:
** 					true - if it is a valid input.
**					false - if it is not a valid input
** Description:	Check if the  duty cycle input  
** 				is valid or not
*/
bool isValidDC ( char* );

/*
** Name: 		turnOff
** Parameters:  int
** Output: 		void
** Description:	Turn off the output
*/
void turnOff ( int );

int
main ( int argc, char* argv [] )
{
	// Check if the input arguments are valid
	if ( !isValidArgument ( argc, argv ))
	{
		return 1;	
	}

	int port_index = atoi ( argv [ 1 ] );
	float duty_cycle =  atof ( argv [ 2 ] );		/* percentage value */
	int pwm_port =  pwm_num [ port_index ];
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
	turnOff ( pwm_port );

	return ( MRAA_SUCCESS );
}
/* end of main */

bool 
isValidArgument ( int argc, char* argv [] )
{
	/* check if the number of arguments is valid */
	if ( argc < 3 )
	{
		printf ( "Usage: %s <port> <duty cycle>\n", argv [ 0 ] );
		printf ( "<port> P0 | P1 | P2 | P3\n" );
		printf ( "<duty cycle> 0.0 - 100.0\n" );
		return false;
	}

	/* check if the  port is valid  */
	int port_index;
	if ( ( port_index = isValidPort ( argv [ 1 ] ) ) == -1 )
	{
		printf ( "Invalid port....\n" );
		printf ( "<port> must be: P0 | P1 | P2 | P3\n" );
		return false;
	}

	/* checks if the argument is  a valid  number */
	if ( !isValidDC ( argv [ 2 ] ) )
	{
		printf ( "Invalid argument....\n" );
		printf ( "<duty cycle> must be a number between: 0.0 and 100.0 \n" );
		return false;
	}

	/*	converts the input argument to floating point
		and checks if it is in the valid interval
	*/
	float duty_cycle =  atof ( argv [ 2 ] );		/* percentage value */
	if ( ( duty_cycle > 100.0 ) || ( duty_cycle  < 0.0 ) )
	{
		printf ( "<duty cycle> must be between: 0.0 and 100.0\n" );
		return false;
	}

	return true;
}

/* end of main */

bool
isValidDC ( char* str )
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

int 
isValidPort ( char* port )
{
	int i;
	for ( i = 0; i < sizeof ( pwm ) / sizeof ( pwm [ 0 ] ); i++ )
	{
		if ( strcmp ( port, pwm [ i ] ) == 0 )
		{
			return i;
		}
	}
	return -1;
}

void
turnOff ( int port )
{
	int OFF = 0;

	mraa_gpio_context p;
	p = mraa_gpio_init ( port );	
	mraa_gpio_dir ( p, MRAA_GPIO_OUT );
	mraa_gpio_write ( p, OFF );
	return;
}

