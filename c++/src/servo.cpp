// Name: pwm.cpp
// Description: Generate a PWM signal to control a servo motor.
// 				The user enters the turn direction: CW or CCW
// Author: Aldo Nunez

#include <iostream>
#include <string>
#include <mraa.hpp>

using namespace mraa;
using std::cout;

// Program: turnServo
// Parameters:	ptr	- Pointer to Pwm
// 				t 	- Period in micro seconds
// 				pw 	- Pulse width
// Output:		None
// Description: Enable, set the period and send
// 				the command to generate pwm signal 				
void turn_servo ( Pwm*, float, float );

enum PWM { PWM0 = 3, PWM1 = 5, PWM2 = 6, PWM3 = 9 } pwm_port; // PWM  ports
const int T ( 20000 ); 				// T period in usec. 20000 ~ 20 ms;  f ~ 50 hz
const float CLKWISE  ( 1.0e-3 );  	// Clockwise, pulse width  1 ms
const float CCLKWISE ( 2.0e-3 );	// Counter Clockwise, pulse width 2 ms

int
main ( int argc, char* argv [] )
{
	if ( argc < 2 )
	{
		cout << "<Usage>: " << argv [ 0 ] << " <DIR>" << "\n";
		cout << "DIR: <CW> or <CCW>" << "\n";

		return 1;
	}

	pwm_port = PWM0;
	Pwm* pwm =  new Pwm ( pwm_port );
	if ( pwm == NULL )
	{
        return ERROR_UNSPECIFIED;
	}

	std::string dir ( argv [ 1 ] );
	if ( !dir.compare ( "CW" ) )
	{
		turn_servo ( pwm, T, CLKWISE );
		dir = "Clockwise";
	}
	else if ( !dir.compare ( "CCW" ) )
	{
		turn_servo ( pwm, T, CCLKWISE );
		dir = "Counter clockwise";
	}
	else
	{
		delete ( pwm );
		cout << "Usage: ./servo <DIR>" << "\n";
		cout << "DIR: <CW> or <CCW>" << "\n";

		return 1;
	}

	cout << "MRAA Version: " << mraa_get_version () << "\n";
	cout << "Platform: " << mraa_get_platform_name () << "\n";
	cout << "PWM port: " << pwm_port << "\n";
	cout << dir << "\n"; 

	std::cin.ignore ();
	delete ( pwm );

	return ( MRAA_SUCCESS );
}

void
turn_servo ( Pwm* ptr, float t, float pw )
{
		ptr -> enable ( true );
		ptr -> period_us ( t ); 
		ptr -> pulsewidth ( pw );

		return;
}
