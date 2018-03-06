// Program: digital_input.cpp
// Description: Read a digital input and display its value
// Author: Aldo Nunez

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using namespace std;

const int PORT ( 5 );

int
main ( void )
{
    // initialize variable with a pin number
    Gpio* port_input = new Gpio ( PORT );

    // set gpio direction to input
	port_input -> dir ( DIR_IN );

    // read port value 
	int value ( port_input -> read () );

	cout << "MRAA Version: " << mraa_get_version () << endl;
	cout << "Platform: " << mraa_get_platform_name () << endl;
	cout << "input port " << PORT << ": " << value  << endl;

	delete ( port_input );

	return ( MRAA_SUCCESS );
}
