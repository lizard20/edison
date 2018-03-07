// Program: servo.py
// Description: Generates a PWM signal to control servo motor
// Author:  Aldo Nunez

var m = require ( 'mraa' );     // module  mraa

const PORT = 3;

const T = 20000;           // Period: 20 msec; f = 50 Hz
const CLKWISE = 1.0e-3
const CCLKWISE = 2.0e-3

if ( process.argv.length < 3 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <DIR>" );
    console.log ( "<DIR>: CW or CCW" );
    process.exit ( 1 );
}

var pwm = new m.Pwm ( PORT );
if ( pwm == null )
{
    process.exit ( 1 );
}

pwm.enable ( true );
pwm.period_us ( T );

turn_dir = process.argv [ 2 ];
if ( turn_dir == "CW" )
{
	pwm.write ( CLKWISE );
}
else if ( turn_dir  == "CCW" ) 
{
	pwm.write ( CCLKWISE );
}
else
{
	console.log ( "<Usage>: " + process.argv [ 0 ] + " <DIR>" );
	console.log ( "<DIR>: CW or CCW" );
    process.exit ( 1 );
}

console.log ( "MRAA Version: " + m.getVersion () );
console.log ( "Platform: " + m.getPlatformName () );
console.log ( "Port Number: " +  PORT );
console.log ( turn_dir == "CW" ? "Clockwise" : "Counter clockwise" );

// pause: to install 'readline-sync': # npm install readline-sync
var readlineSync = require ('readline-sync');
readlineSync.keyInPause();
pwm.write ( 0 );

