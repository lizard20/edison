//
// Program: digital_input_io.cpp
// Description: Read one of the digital input ports
//                between  0 and 13 and displays
//                its value
// Author: Aldo Nunez
//

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using namespace std;

// error messages 
string message1 = "Usage: ";
string message2 = "<port>: 0 | 1 | 2 | 3 | 4 | 5 |.....| 13 ";
string  message3 = "<port> must be between: 0..13";
	
// Number of digital input ports
const unsigned int PORTS ( 13 );

//
// Name:        isValid
// Parameters:  string input
// Output:      Boolean
//              true - if the input is an integer number.
//              false - if the input is not an integer number
// Description: Check if the input is an integer number
//
bool isValid ( char* );

int
main ( int argc, char* argv[] )
{
	message1 = message1 + argv [ 0 ] + " <port>";
	// Check the number of arguments
	if ( argc < 2 )
	{
		cout  << message1 << endl;
        cout << message2 << endl;
		exit ( 1 );
	}

    // Check if the argument is a number 
    if ( !isValid ( argv [ 1 ] ) )
    {
		cerr << message1  << endl;
        cerr << message2  << endl;
        exit ( 1 );
    }

    int port_number =  atoi ( argv [ 1 ] );

    // Check if the number is between: 0 - 13 
    if ( ( port_number < 0 ) || ( port_number  > PORTS ) )
    {
		cerr << message3  << endl;
    	cerr << message2  << endl;
        exit ( 1 );
    }

    // create access to gpio  pin
    Gpio* input_port = new Gpio ( port_number );
    if ( input_port == NULL )
    {
        return ERROR_UNSPECIFIED;
    }

    // set gpio drection to  out
    Result response = input_port -> dir  ( DIR_IN );
    if ( response != SUCCESS )
    {
         printError ( response );
         exit ( 1 );
     }

    // read port
    int value = input_port -> read ();
    if ( value == -1 )
    {
        fprintf (stderr, "Failed reading port %d", input_port );
        exit ( 1 );
    }

    cout << "MRAA Version: " << getVersion () << endl;
    cout << "Platform: " << getPlatformName () << endl;
    cout << "Input port: " << port_number << ": " << value << endl;

    delete ( input_port );
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

