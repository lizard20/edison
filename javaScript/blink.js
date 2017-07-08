// Program: blink.js
// Description: blink LED
// Author: Aldo Nunez
 
module  mraa
var m = require ( 'mraa' );

// choose pin
var led = new m.Gpio ( 13 );

// set the gpio direction
led.dir ( m.DIR_OUT );

var flag = true;

// set time interval
setInterval ( toogle, 1000 );

// turn on and turn off led
function toogle ()
{
    flag ? led.write ( 1 ): led.write ( 0 );
    flag ^= true;
}
