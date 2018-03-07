'''
 Program: analog_input.py
 Description: Read analog input and displays its value
 Author: Aldo Nunez
'''

import time
import sys
import mraa as m

# ADC resolution
NBITS = 12 

# Number of analog ports
N = 6

PORTS = list ( range ( N ) )

def main ( argv ):
    try:
        port =  int ( sys.argv [ 1 ] )
    except:
        print ( "Usage: python " + sys.argv [ 0 ] + " <port>" )
        print ( "<port>: 0 | 1 | 2 | 3 | 4 | 5 " )
        sys.exit ()

    #Check if the number is between: 0 - 5
    if not ( port in PORTS ):
        print ( "<port>: 0 | 1 | 2 | 3 | 4 | 5 " )
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
        print ( "ADC " + sys.argv [ 1 ] + " read float: "  + "%.5f" % round (  floatValue, 5 ) )
        time.sleep ( 1 )

if __name__ == "__main__":
    main ( sys.argv [ 1: ] )
    
