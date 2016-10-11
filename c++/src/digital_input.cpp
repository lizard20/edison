// Program: digital_input.cpp
// Description: Read digital input and display its value
// Author: Aldo Nunez

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using std::cout;

const int PIN_INPUT ( 5 );

int
main ( void )
{
	int iopin ( PIN_INPUT );
	Gpio* gpio = new Gpio ( iopin );

    if ( gpio == NULL )
	{
        return ERROR_UNSPECIFIED;
    }

	Result input = gpio -> dir ( DIR_IN );

    if ( input != SUCCESS )
	{
        printError ( input );
        return ERROR_UNSPECIFIED;
    }

	int value ( gpio -> read () );

	cout << "MRAA Version: " << mraa_get_version () << "\n";
	cout << "Platform: " << mraa_get_platform_name () << "\n";
	cout << "input pin_" << PIN_INPUT << ": " << value  << "\n";

	delete ( gpio );

	return ( MRAA_SUCCESS );
}
