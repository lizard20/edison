// Name: pwm.cpp
// Description: Generate a PWM output. The user enters 
// 				the percentage of  duty cycle
// Author: Aldo Nunez

#include <iostream>
#include <mraa.hpp>

using namespace mraa;

enum PWM { PWM0 = 3, PWM1 = 5, PWM2 = 6, PWM3 = 9 } pwm_port;
const int T ( 20000 ); 		// T ~ period in usec 

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
		std::cout << "Usage: " << argv [ 0 ] << " <number>" << std::endl;  
		return 1;
	}

	if ( !isValid ( argv [ 1 ] ) )
	{
		std::cout << "Invalid argument...." << "\n";
		std::cout << "Argument must be a number between: 0.0 - 100.0" << "\n";
		return 1;	
	}
	
	float v ( atof ( argv [ 1 ] ) );		// percentage value
	
	if ( ( v > 100.0 ) || ( v  < 0.0 ) )
	{
		std::cout << "<number> must be between: 0.0 and 100.0" << std::endl;
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
	pwm -> write ( v / 100.0 );    

	std::cout << "MRAA Version: " << mraa_get_version () << "\n";
	std::cout << "Platform: " << mraa_get_platform_name () << "\n";
	std::cout << "Port Number: " << pwm_port << "\n";
	std::cout << "Period: " << T * 1.0e-6 << " sec" << "\n";
	std::cout << "Frequency: " << 1.0e6 / T << " Hz" << "\n";
	std::cout << "Percentage of PWM: " << 100 *  pwm -> read ( ) <<  "%" << "\n";
	std::cout << "Press \"Enter\" to finish." << "\n";

	getchar ();
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


