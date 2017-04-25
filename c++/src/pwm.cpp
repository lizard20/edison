// Name: pwm.cpp
// Description: Generates a PWM output. The user enters
// 				the percentage of  duty cycle
// Author: Aldo Nunez

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using std::cout;


enum PWM { PWM0 = 3, PWM1 = 5, PWM2 = 6, PWM3 = 9 } pwm_port;
const int T ( 20000 ); 		// T - period in usec

// Name: 		isValid
// Parameters:  pointer to string
// Output: 		Boolean, true - if it is a valid input.
// 				false - if it is not a valid input
// Description:	Check if the input is a number or a
// 				decimal point.
bool isValid ( char* );

int
main ( int argc, char* argv [] )
{
	if ( argc < 2 )
	{
		cout << "Usage: " << argv [ 0 ] << " <duty cycle>" << std::endl;
		cout << "<duty cycle> 0.0 ... 100.0" << std::endl;

		return 1;
	}

	if ( !isValid ( argv [ 1 ] ) )
	{
		cout << "Invalid argument...." << "\n";
		cout << "<duty cycle> must be a number between: 0.0 - 100.0" << "\n";

		return 1;
	}

	float dutyCycle ( atof ( argv [ 1 ] ) );		// percentage value

	if ( ( dutyCycle > 100.0 ) || ( dutyCycle  < 0.0 ) )
	{
		cout << "<ducty cycle> must be between: 0.0 - 100.0" << std::endl;

		return 1;
	}

	pwm_port = PWM0;
	Pwm* pwm = new Pwm ( pwm_port );
	if ( pwm == NULL )
	{
        return ERROR_UNSPECIFIED;
	}

	pwm -> enable ( true );
	pwm -> period_us ( T );		// f ~ 1/T
	pwm -> write ( dutyCycle / 100.0 );

	cout << "MRAA Version: " << mraa_get_version () << "\n";
	cout << "Platform: " << mraa_get_platform_name () << "\n";
	cout << "Port Number: " << pwm_port << "\n";
	cout << "Period: " << T * 1.0e-6 << " sec" << "\n";
	cout << "Frequency: " << 1.0e6 / T << " Hz" << "\n";
	cout << "Percentage of PWM: " << 100 *  pwm -> read () << "\n";
	cout << "Press \"Enter\" to finish." << "\n";

	std::cin.ignore ();
	delete ( pwm );

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


