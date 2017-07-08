// Program: digital_input_io.js
// Description: Read one of the digital input ports
//              between  0 and 13 and displays
//              its value
// Author: Aldo Nunez

// mraa module
var m = require ( 'mraa' );

// number of digital output ports
const PORTS = 14

if ( process.argv.length < 3 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" );
    console.log ( "<port>: 0 | 1 | 2 | 3 | ... | 13 " );

    process.exit ( 1 );
}

var input_port = Number ( process.argv [ 2 ] );

// Check if the argument is a number
if ( !Number.isInteger ( input_port ) )
{
    console.log ( "<port> must be an integer number: 0 | 1 | 2 | 3 |...| 13" );

    process.exit ( 1 );
}

// Check if the number is between: 0 - 13
if ( ( input_port < 0  ) || ( input_port  > PORTS - 1 )  )
{
    console.log ( "<port> must be an integer number between: 0 - 13" );

    process.exit ( 1 );
}

// choose pin
var pin_input = new m.Gpio ( input_port );

// set the gpio direction
var response = pin_input.dir ( m.DIR_IN );
if ( response )
{
    process.exit ( 1 );
}

var value = pin_input.read ();
if ( value == -1 )
{
    fprintf (stderr, "Failed reading port %d", pin_input );
    exit ( 1 );
}

console.log ( "MRAA Version: " + m.getVersion () );
console.log ( "Platform: " + m.getPlatformName () );
console.log ( "Input port ", input_port, + ": " +  value );




