// Program: analog_input.js
// Description: Read analog input and display its value
// Author: Aldo Nunez

var m = require ( 'mraa' );     // module  mraa

const ANALOG_IN = { A0: 0, A1: 1, A2: 2, A3: 3, A4: 4, A5: 5 };  // analog ports: A0 - A5
const  NBITS  = 12;            // number of bits

// Check if the number of arguments is 3
if ( process.argv.length < 3 )
{
    console.log ( "Usage: " + process.argv [ 1 ].split ( "/") [ 5 ] + " <port>" );
    console.log ( "<port>: 0 | 1 | 2 | 3 | 4 | 5" );

    process.exit ( 1 );
}

var port = Number ( process.argv [ 2 ] );

// Check if the argument is a number
if ( !Number.isInteger ( port ) )
{
    console.log ( "<port> must be an integer number: 0 | 1 | 2 | 3 | 4 | 5" );

    process.exit ( 1 );
}

// Check if the number is between: 0 - 5
if ( ( port < 0 ) || ( port  > 5 )  )
{
    console.log ( "<port> must be an integer number between: 0 - 5" );

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
