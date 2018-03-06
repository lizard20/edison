// Program: pwm.js
// Description: Read analog input and display its value
// Author: Aldo Nunez

var m = require ( 'mraa' );     // module  mraa

message = "<port>: P0 | P1 | P2 | P3";

const PWM  = { P0: 3, P1: 5, P2: 6, P3: 9 };  // pwm ports: 

// Check if the number of arguments is 3
if ( process.argv.length < 3 )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" );
    console.log ( message );
    process.exit ( 1 );
}

var port = Number ( process.argv [ 2 ] );

// Check if the argument is a number
if ( !Number.isInteger ( port ) )
{
    console.log ( "Usage: node " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" );
    console.log ( message );
    process.exit ( 1 );
}

// Check if the number is between: 0 - 5
if ( ( port < 0 ) || ( port  > 5 )  )
{
    console.log ( message );
    process.exit ( 1 );
}

var aInput = new m.Aio ( port );

if ( aInput == null )
{
    process.exit ( 1 );

}

aInput.setBit ( NBITS );        // configure # of bits of ADC

console.log ( "MRAA Version: " + m.getVersion () );
console.log ( "Platform: " + m.getPlatformName () );

while ( 1 )
{
    intValue = aInput.read ();           // reading integer value
    floatValue = aInput.readFloat ();    // reading float value
    console.log ( "ADC " + port +  " read integer: " + intValue );
    console.log ( "ADC " + port +  " read float:  " +  floatValue.toFixed ( 5 ) );
    sleep ( 1000 );
}

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
