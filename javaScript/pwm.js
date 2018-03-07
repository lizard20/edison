// Name: pwm.js
//  Description: Generate a PWM output. The user enters 
//              the port and the percentage of duty cycle
//  Author: Aldo Nunez

var m = require ( 'mraa' );     // module  mraa

message1 = "<port>: P0 | P1 | P2 | P3";
message2 = "<duty cycle>: 0.0 - 100.0";

const T = 20000;  // T - period in usec

const PWM  = { "P0": 3, "P1": 5, "P2": 6, "P3": 9 };  // pwm ports: 

// Check if the number of arguments is 3
if ( process.argv.length < 4 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" + " <duty cycle>" );
    console.log ( message1 );
    console.log ( message2 );
    process.exit ( 1 );
}
// Check for  the input port
var port = process.argv [ 2 ];

if ( !(port in PWM)  )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" + " <duty cycle>" );
    console.log ( message1 );
    console.log ( message2 );
    process.exit ( 1 );
}

var duty_cycle = Number ( process.argv [ 3 ] );

// Check if the duty cycle is between 0-100
if ( duty_cycle  < 0 || duty_cycle > 100 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" + " <duty cycle>" );
    console.log ( message1 );
    console.log ( message2 );
    process.exit ( 1 );
}

var pwm = new m.Pwm ( PWM [ port ] );
if ( pwm == null )
{
    process.exit ( 1 );
}

pwm.enable ( true );
pwm.period_us ( T );
pwm.write ( duty_cycle / 100.0);

console.log ( "MRAA Version: " + m.getVersion () );
console.log ( "Platform: " + m.getPlatformName () );
console.log ( "PWM: " + port );
console.log ( "Port Numbe2r: " + PWM [ port ] );
console.log ( "Period: " + T * 1.0e-6 + " sec" );
console.log ( "Frequency: " +  1.0e6 / T  + " Hz" );
console.log ( "Percentage of PWM: ", duty_cycle + ' \%' );

// pause: to install 'readline-sync': # npm install readline-sync
var readlineSync = require ('readline-sync');
readlineSync.keyInPause();
pwm.write ( 0 );





