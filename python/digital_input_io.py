'''
Program: digital_input_io.cpp
Description: Read one of the digital input ports
            between  0 and 13 and displays
            its value
Author: Aldo Nunez
'''

import mraa as m
import sys

# Number of digital output ports
N = 14

ports  = list ( range ( N ) )

def main ( argv ):
    try:
        port_number =  int ( sys.argv [ 1 ] )
    except:
        print ( "Usage: python %s <port>" %  sys.argv [ 0 ]  )
        print ( "<port>: 0 | 1 | 2 | 3 |...| 13 " )
        sys.exit ()

    if not ( port_number in ports ):
        print ( "<port> must be  between: %d..%d" % ( min ( ports ), max ( ports ) ) )
        print ( "<port>: 0 | 1 | 2 | 3 |...| 13 " )
        sys.exit ()

    input_port = m.Gpio ( port_number )
    if input_port == None:
        sys.exit ()

    response = input_port.dir ( m.DIR_IN )
    if response != m.SUCCESS:
        m.printError ( response )
        sys.exit ()

    value  = input_port.read ()
    if value == -1:
        print ( "Failed reading port %d" % input_port );
        sys.exit() 

    print ( "MRAA Version: %s" %  m.getVersion () )
    print ( "Platform: %s" % m.getPlatformName () )
    print ( "Input port %s: %s" % ( str ( port_number ), str ( value ) ) )

if __name__ == "__main__":
    main ( sys.argv [ 1: ] )
