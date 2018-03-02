//
// Program: blink_io.cpp
// Description: blink any LED connected to
//				14 ouput ports
// Author: Aldo Nunez
//

#include <iostream>
#include <csignal>
#include <string>
#include <mraa.hpp>

using namespace std;
using namespace mraa;

/* OFF = 0, ON = 1 */
enum STATE { OFF, ON };

 /* number of digital oputput ports  */
const unsigned int  PORTS ( 14 );
//enum DIGITAL_OUT { IO0, IO1, IO2, IO3, IO4, IO5, IO6, IO7, IO8, IO9, IO10, IO11, IO12, IO13} digital_output;

const useconds_t T = 1e6;	/* 1e6 ~ 1 sec */

volatile sig_atomic_t  flag ( 1 );

/************  Functions prototypes ************/
/*
** Name:      	isValidArgument
** Parameters:  1.- Integer,  number of arguments
** 				2.- Initail address of  pointers array to char
** Output:      Boolean
                true - 	if the input is a valid argument.
						if it is an integer number, and  it 
						is between 0 and 13
**              false - if it is not an integer number between
**              0 - 13
** Description: Check if the inputs are valid arguments
*/
bool isValidArgument ( int, char* [] );

/*
** Name:        isValid
** Parameters:  string input
** Output:      Boolean
                true - if the input is an integer number.
**              false - if the input is not an integer number
** Description: Check if the input is an integer number
*/
bool isNumber ( char* );

/*
** Name: manage_signal
** Input: Integer
** Output: None
** Description: Catch the signal interrupt,
** 				'Ctrl + c' signal  generated
** 				by the user  and  modify
** 				flag variable
*/
void manage_signal ( int );

int
main ( int argc, char* argv [] )
{
	if ( !isValidArgument ( argc, argv ) )
	{
		return 1;
	}
 	int port =  atoi ( argv [ 1 ] );

	// create access to gpio  pin
	Gpio* led = new Gpio ( port );
	if ( led == NULL )
	{
		return ERROR_UNSPECIFIED;
	}


	// set gpio drection to  out
	Result response = led -> dir  ( DIR_OUT );
    if ( response != SUCCESS )
    {
         printError ( response );
     }

    cout << "blinking port " << port << "..." << endl;
	cout <<  "To finish press: Ctrl + c" << endl;

 	signal ( SIGINT, manage_signal );

 	// blink indefinitely until "Ctrl + c"
	while ( flag )
 	{
 		response  = led -> write ( ON );
         if ( response != SUCCESS )
         {
          	printError ( response );
         }

         usleep ( T );

         response = led -> write ( OFF );
         if ( response != SUCCESS )
         {
             printError ( response );
         }

 		usleep ( T );
 	}

 	delete ( led );

 	return 0;
}
// end of main

bool
isValidArgument ( int argc, char* argv [] )
{
	/* Check the number of arguments*/
    if ( argc < 2 )
	{
		cerr << "Usage: " << argv [ 0 ] << endl;
        cerr << "<port>: 0 | 1 | 2 | 3 | 4 | 5 |.....| 13" << endl;

		return false;
	}

	/* Check if the argument is an integer number */
    if ( !isNumber ( argv [ 1 ] ) )
    {
        cerr << "<port> must be an integer number between: 0 - 13" << endl;

        return false;
    }

  	int port =  atoi ( argv [ 1 ] );

    // Check if the number is between: 0 - 13
    if ( ( port < 0 ) || ( port  > PORTS - 1 ) )
    {
        cerr <<  "<port> must be an integer number between: 0 - 13" << endl;

        return false;
    }
	
	return true;
}

bool
isNumber ( char* str )
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

void
manage_signal ( int sig )
{
	if ( sig == SIGINT )
	{
		flag = 0;
	}
	cout << endl << "program is closing ..." << endl;

	return;
}
