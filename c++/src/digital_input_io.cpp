/*
** Program: digital_input_io.cpp
** Description: Read one of the digital input ports
                between  0 and 13 and displays
                its value
** Author: Aldo Nunez
*/

#include <iostream>
#include <mraa.hpp>

using namespace mraa;
using namespace std;

/* Number of digital input ports*/
const unsigned int PORTS ( 13 );

/*
** Name:        isValid
** Parameters:  string input
** Output:      Boolean
                true - if the input is an integer number.
**              false - if the input is not an integer number
** Description: Check if the input is an integer number
*/
bool isValid ( char* );

int
main ( int argc, char* argv[] )
{
	if ( argc < 2 )
	{
		cout  << "Usage: <port>" << argv [ 0 ] << endl;
        cout << "<port>: 0 | 1 | 2 | 3 | 4 | 5 |.....| 13"  << endl;
		return 1;
	}

    /* Check if the argument is a number */
    if ( !isValid ( argv [ 1 ] ) )
    {
        cout <<  "<port> must be an integer number between: 0 - 13" << endl;

        return 1;
    }

    int port_number =  atoi ( argv [ 1 ] );

    /* Check if the number is between: 0 - 13 */
    if ( ( port_number < 0 ) || ( port_number  > PORTS ) )
    {
        cout <<  "<port> must be an integer number between: 0 - 13" << endl;

        return 1;
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
         return 1;
     }

    /* read port*/
    int value = input_port -> read ();
    if ( value == -1 )
    {
        fprintf (stderr, "Failed reading port %d", input_port );

        return  1;
    }

    cout << "MRAA Version: " << getVersion () << endl;
    cout << "Platform: " << getPlatformType () << endl;
    cout << "Input port: " << input_port << ": " << value << endl;

    delete ( input_port );

    return ( MRAA_SUCCESS );


	return 0;
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
