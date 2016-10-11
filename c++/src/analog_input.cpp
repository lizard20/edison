// Program: analog_input.cpp
// Description: Read analog input and display its value
// Author: Aldo Nunez

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using std::cout;

// Name: 		isValid
// Parameters:  pointer to string
// Output: 		Boolean, true - if it is a valid input. 	
// 				false - if it is not a valid input
// Description:	Check if the input is an integer number
bool isValid ( char* );

enum ANALOG_IN { A0, A1, A2, A3, A4, A5 };	// analog ports: A0 - A5
const int NBITS  ( 12 );			// number of bits 

int
main ( int argc, char* argv[] )
{
	if ( argc < 2 )
	{
		cout << "Usage: " << argv [ 0 ] << " <port>" << std::endl;  
		cout << "<port>: 0..5" << std::endl;  
		return 1;
	}

	if ( !isValid ( argv [ 1 ] ) )
	{
		cout << "<port> must be between: 0..5" << "\n";
		return 1;	
	}
	
	float port ( atof ( argv [ 1 ] ) );
	
	if ( ( port < A0 ) || ( port  > A5 ) )
	{
		cout << "<port> must be between: 0..5" << std::endl;
		return 1;
	}


	uint16_t intValue ( 0 );		// variable  to read integer value
	float floatValue ( 0.0 );		// variable to read float value

	Aio* aInput = new Aio ( port );

	if ( aInput == NULL )
	{
        return MRAA_ERROR_UNSPECIFIED;
    }

	aInput -> setBit ( NBITS ); 		// configure # of bits of ADC

	cout << "MRAA Version: " << mraa_get_version () << "\n";
	cout << "Platform: " << mraa_get_platform_name () << "\n";
	while ( 1 )
	{
		intValue = aInput -> read ();			// reading integer value
		floatValue = aInput -> readFloat ();	// reading float value
        cout << "ADC " << port <<  " read integer: " << intValue << "\n";
        cout << "ADC " << port <<  " read float:  " <<  floatValue << "\n";
		sleep ( 1 );
    }

	delete ( aInput );

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


