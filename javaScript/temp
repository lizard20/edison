// Program: blink.js
// Description: blink LED
// Author: Aldo Nunez

var m = require ( 'mraa' ); 	// module  mraa

const STATE  = { OFF: 0, ON: 1 };
const LED = 13;					// 13 ~ led DS2
const T = 1000;					// 1000 ~ 1 msec 

var led = new m.Gpio ( LED ); 	// choose pin  
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
	led.write ( STATE.ON );
	sleep ( T );			
	led.write ( STATE.OFF );
	sleep ( T );
}
