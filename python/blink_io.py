'''
 Program: blink_io.py
 Description: blink LED
 Author: Aldo Nunez
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
        print ( "Usage: python " + sys.argv [ 0 ] + " <port>" )
        print ( "<port>: 0 | 1 | 2 | 3 |...| 13 " )
        sys.exit ()

    if port < ports [ 0 ] or port > ( len ( ports ) ):
        print ( "<port> must be an integer number between: %d - %d" % ( ports [ 0 ], len ( ports ) - 1 ) )
        sys.exit ()

    led = m.Gpio ( port )
    if led == None:
        sys.exit ()

    response = led.dir ( m.DIR_OUT )
    if response != m.SUCCESS:
        m.printError ( r )
        sys.exit()

    print ( "MRAA Version: " +  m.getVersion () )
    print ( "Platform: " + m.getPlatformName () )
    print ( "blinking port %d ..." %  port )
    print ( "To finish press: Ctrl + c" )

    try:
        while True:
            response = led.write ( ON )
            if response != m.SUCCESS:
                m.printError ( r )

            time.sleep ( T )

            response = led.write ( OFF )
            if response != m.SUCCESS:
                m.printError ( r )

            time.sleep ( T )
    except KeyboardInterrupt:
        led.write ( OFF )
        print ( "\nprogram is closing..." )
        sys.exit ( 0 )

if __name__ == "__main__":
    main ()
