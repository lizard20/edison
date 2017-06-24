'''
** Program: blink_io.py
** Description: blink any LED connected to pines
                IO0 to IO13
** Author: Aldo Nunez
'''

import mraa as m
import time
import sys


# STATES
OFF = 0
ON = 1

# PORTS
N = 14

ports = [ i for i in range ( N ) ]

# time
T =  1.0    # 1.0 ~ 1 sec

def main():
    try:
        port =  int ( sys.argv [ 1 ] )
    except:
        print ( "Usage: python %s <port>" % sys.argv [ 0 ] )
        print ( "<port>: 0 | 1 | 2 | 3 |...| 13 " )
        sys.exit ()

    if port < min( ports ) or port > max ( ports ):
        print ( "<port> must be an integer number between: %d - %d" % ( min ( ports ), max ( ports ) ) )
        sys.exit ()

    led = m.Gpio ( port )
    if led == None:
        sys.exit ()

    response = led.dir ( m.DIR_OUT )
    if response != m.SUCCESS:
        m.printError ( response )
        sys.exit()

    print ( "MRAA Version: %s" %  m.getVersion () )
    print ( "Platform: %s" % m.getPlatformName () )
    print ( "blinking port %d ..." %  port )
    print ( "To finish press: Ctrl + c" )

    try:
        while True:
            response = led.write ( ON )
            if response != m.SUCCESS:
                m.printError ( response )

            time.sleep ( T )

            response = led.write ( OFF )
            if response != m.SUCCESS:
                m.printError ( response )

            time.sleep ( T )
    except KeyboardInterrupt:
        led.write ( OFF )
        print ( "\nprogram is closing..." )
        sys.exit ( 0 )

if __name__ == "__main__":
    main ()
