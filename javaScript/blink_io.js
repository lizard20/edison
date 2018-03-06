// Program: blink_io.js
// Description: blink any LED connected to ports
//              0 to 13
// Author: Aldo Nunez

// mraa module
var m = require ( 'mraa' );

// errrors  message
message1 = "<port>: 0 | 1 | 2 | 3 | ... | 13";

// number of digital output ports
const PORTS = 14

// states
const STATES = {OFF: 0, ON: 1 };

// time in milliseconds
const T = 100;

if ( process.argv.length < 3 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" );
    console.log ( message1 );

    process.exit ( 1 );
}

var port = Number ( process.argv [ 2 ] );

// Check if the argument is a number
if ( !Number.isInteger ( port ) )
{
    console.log ( message1 );

    process.exit ( 1 );
}

// Check if the number is between: 0 - 13
if ( ( port < 0  ) || ( port  > PORTS - 1 )  )
{
	console.log ( "<port> must be between: 0..13");
    console.log ( message1 );
    process.exit ( 1 );
}

// choose pin
var led = new m.Gpio ( port );

// set the gpio direction
var response = led.dir ( m.DIR_OUT );
if ( response )
{
    process.exit ( 1 );
}

console.log ( "MRAA Version: " + m.getVersion () );
console.log ( "Platform: " + m.getPlatformName () );
console.log ( "blinking port " + port +  " ..." );
console.log ( "To finish press: Ctrl + c" );

var flag = true;

// set time interval
setInterval ( toogle, T );

// turn on and turn off led
function toogle ()
{
    flag ? led.write ( STATES.ON ): led.write ( STATES.OFF );
    flag ^= true;
}

// catch Ctrl + c
process.on('SIGINT', function()
{
    led.write ( STATES.OFF )
    console.log ( "\nprogram is closing ..." );
    process.exit ( 1 );
});

