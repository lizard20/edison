// Name: pwm.cpp
// Description: Generates a PWM output. The user enters
// 				the port name  and the percentage of duty cycle
// Author: Aldo Nunez

var m = require("mraa");
const message1 = "test";

const PWM = { P0: 3, P1: 5, P2: 6, P3: 9 };  // analog ports: P0 - P3
const T = 2000

if ( process.argv.length < 4 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" + " <duty_cycle>" );
    console.log ( message1 );
    process.exit ( 1 );
}




//var pwm = new m.Pwm ( 3 );  // initialize PWM on digital pin #3
//pwm.enable ( true );
//pwm.period_us ( T );
//pwm.write ( T / 100.0);
//


