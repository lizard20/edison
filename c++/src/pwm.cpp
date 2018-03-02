// Name: pwm.cpp
// Description: Generates a PWM output. The user enters
// 				the port name  and the percentage of duty cycle
// Author: Aldo Nunez

#include <iostream>
#include <string>
#include <mraa.hpp>

using namespace mraa;
using namespace std;

const int gpio [] = { 3, 5, 6, 9 };
const string pwm [] = { "P0", "P1", "P2", "P3" };
const int T ( 20000 ); 		// T - period in usec

// Name: 		isValidPort
// Parameters:  String
// Output: 		Integer:
// 					port index number
// 					-1, if it is not a valid port.
// Description:	Check if the input is a valid port.
// 				If it is a valid port, return port index number
// 				If it is not a valid port, return -1
int isValidPort ( string );

// Name: 		isValidDC
// Parameters:  String
// Output: 		Boolean, true - if it is a valid input.
// 				false - if it is not a valid input
// Description:	Check if the input is a number or a
// 				decimal point.
bool isValidDC ( string );

//  Name: 		turnOff
// Parameters:  int
// Output: 		void
// Description:	Turn off the output
void turnOff ( int );

int
main ( int argc, char* argv [] )
{
	if ( argc < 3 )
	{
		cout << "Usage: " << argv [ 0 ] << "<port>" << " <duty cycle>" << endl;
		cout << "<port>: " << pwm [ 0 ] << " | " << pwm [ 1 ] << " | " <<  pwm [ 2 ] <<  " | " <<  pwm [ 3 ] << endl;
		cout << "<duty cycle>: 0.0 - 100.0" << endl;
		return 1;
	}

	 // check if it is a valid  port
	int port_index;
	if ( ( port_index = isValidPort ( argv [ 1 ] ) ) == -1 )
	{
		cout <<  "Invalid port...." << endl;
		cout << "<port> must be: " << pwm [ 0 ] << " | " << pwm [ 1 ] << " | " <<  pwm [ 2 ] <<  " | " <<  pwm [ 3 ] << endl;
		return 1;
	}

	// check if it is a valid duty cycle
	if ( !isValidDC ( argv [ 2 ] ) )
	{
		cout << "Invalid argument...." << "\n";
		cout << "<duty cycle> must be a number between: 0.0 - 100.0" << endl;
		return 1;
	}

	// convert the input argument to floating point
	// and check if it is in the valid interval
	float dutyCycle ( atof ( argv [ 2 ] ) );		// percentage value
	if ( ( dutyCycle > 100.0 ) || ( dutyCycle  < 0.0 ) )
	{
		cout << "<duty cycle> must be between: 0.0 - 100.0" << endl;
		return 1;
	}

	int pwm_port ( gpio [ port_index ] );
	Pwm* pwm = new Pwm ( pwm_port );
	if ( pwm == NULL )
	{
        return ERROR_UNSPECIFIED;
	}

	pwm -> enable ( true );
	pwm -> period_us ( T );		// f ~ 1/T
	pwm -> write ( dutyCycle / 100.0 );

	cout << "MRAA Version: " << mraa_get_version () << endl;
	cout << "Platform: " << mraa_get_platform_name () << endl;
	cout << "Port Number: " << pwm_port << endl;
	cout << "Period: " << T * 1.0e-6 << " sec" << endl;
	cout << "Frequency: " << 1.0e6 / T << " Hz" << endl;
	cout << "Percentage of PWM: " << 100 *  pwm -> read () << endl;
	cout << "Press \"Enter\" to finish." << endl;

	cin.ignore ();
	delete ( pwm );
	turnOff ( pwm_port );

	return ( MRAA_SUCCESS );
}

bool
isValidDC ( string s )
{
	int i ( 0 );

	while ( s [ i ] != 0 )
	{
		if ( !isdigit ( s [ i ] )  &&  ( s [ i ] != '.' ) )
		{
			return false;
		}
		i++;
	}
	return true;
}

int 
isValidPort ( string port )
{
	for ( int i ( 0 ); i < sizeof ( pwm ) / sizeof ( pwm [ 0 ] ); i++ )
	{
		if ( port.compare ( pwm [ i ] ) == 0 )
		{
			return i;
		}
	}
	return -1;
}

void
turnOff ( int port )
{
	int OFF ( 0 );

	mraa::Gpio p ( port );
	mraa::Result response = p.dir ( mraa::DIR_OUT );
	p.write ( OFF );
	return;
}
