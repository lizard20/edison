'''
 Program: analog_input.py
 Description: Read analog input and displays its value
 Author: Aldo Nunez 
'''

import time
import sys
import mraa as m

NBITS = 12

try:
    port =  int ( sys.argv [ 1 ] )
except:
    print ( "Usage: python " + sys.argv [ 0 ] + " <PORT>" )
    print ( "<PORT>: 0..5" )
    sys.exit ()

if ( port > 5 ) or ( port < 0 ):
    print ( "<Port>: 0..5" )
    sys.exit ()

analogIn = m.Aio ( port )
analogIn.setBit ( NBITS )

print ( "MRAA Version: " +  m.getVersion () )
print ( "Platform: " + m.getPlatformName () )
print ( "Analog port: " + str ( port ) )

while True:
	intValue =  analogIn.read ()
	floatValue =  analogIn.readFloat ()
        print ( "ADC " + sys.argv [ 1 ] + " read integer: " + str ( intValue )  )
        print ( "ADC " + sys.argv [ 1 ] + " read float: "  + str ( floatValue ) )
	time.sleep ( 1 )
