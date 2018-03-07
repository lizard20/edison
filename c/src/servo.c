/*
** Name: servo.c
** Description: Generate a PWM signal to control a servo motor.
** 				The user enters the turn direction: CW or CCW
** Author: Aldo Nunez
*/

#include <stdio.h>
#include <string.h>
#include <mraa.h>

/*
** Program: turnServo
** Parameters:	ptr	- Pointer to Pwm
**				t 	- Period in micro seconds
** 				pw 	- Pulse width
** Output:		None
** Description: Enable, set the period and send
**				the command to generate pwm signal 				
*/
void turn_servo ( mraa_pwm_context*, float, float );

enum PWM { PWM0 = 3, PWM1 = 5, PWM2 = 6, PWM3 = 9 } pwm_port; /* PWM  ports */
const int T = 20000 ; 				/* T period in usec. 20000 ~ 20 ms;  f ~ 50 hz */
const float CLKWISE = 1.0e-3;  		/* Clockwise, pulse width  1 ms */
const float CCLKWISE = 2.0e-3;		/* Counter Clockwise, pulse width 2 ms */

int
main ( int argc, char* argv [] )
{
	if ( argc < 2 )
	{
		printf ( "<Usage>: %s <DIR> \n", argv [ 0 ] );
		printf ( "DIR: <CW> or <CCW> \n" );

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

	char* dir =  argv [ 1 ];
	if ( !strcmp ( dir, "CW" ) )
	{
		turn_servo ( &pwm, T, CLKWISE );
		dir = "Clockwise";
	}
	else if ( !strcmp ( dir, "CCW" ) )
	{
		turn_servo ( &pwm, T, CCLKWISE );
		dir = "Counter clockwise";
	}
	else
	{
		printf ( "Usage: ./servo <DIR> \n" );
		printf ( "DIR: <CW> or <CCW> \n" );

		return 1;
	}

	printf ( "MRAA Version: %s \n", mraa_get_version () );
	printf ( "Platform: %s \n", mraa_get_platform_name () );
	printf ( "PWM port: %d \n", pwm_port );
	printf ( "%s \n", dir ); 

	getchar ();
	mraa_pwm_close ( pwm );

	return ( MRAA_SUCCESS );
}

void
turn_servo ( mraa_pwm_context* ptr, float t, float pw )
{
		mraa_pwm_enable ( *ptr, 1 );
		mraa_pwm_period_us (  *ptr, t ); 
		mraa_pwm_pulsewidth ( *ptr, pw );

		return;
}
