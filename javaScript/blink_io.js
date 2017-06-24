// Program: blink.js
// Description: blink LED
// Author: Aldo Nunez

var m = require ( 'mraa' ); 	// module  mraa


var led = new m.Gpio ( 13 ); 	// choose pin
led.dir ( m.DIR_OUT ); 			// set the gpio direction


// Name: sleep
// Input: The number of milliseconds
// Output:
// Description: Produce a delay of n milliseconds
function sleep ( n )
{
	var start = new Date().getTime();
	while ( ( new Date().getTime () - start ) < n )
	{}
}

while ( 1 )
{
	led.write ( 1 );
	sleep ( 1 );
	led.write ( 0 );
	sleep ( 1 );
}
