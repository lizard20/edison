''' 
 Name: pwm.py
 Description: Generate a PWM output. The user enters 
              the port and the percentage of duty cycle
 Author: Aldo Nunez
'''

import mraa as m
import sys

PWM = { 'P0':3, 'P1':5, 'P2':6, 'P3':9 }
T = 20000    # Period: 20000 usec ~ 50 Hz

''' 
 Name:          isValidPort
 Parameters:    string
 Output:         True - if it is a valid input. 	
 		False - if it is not a valid input
 Description:	Check if the input is a valid number 
'''
def isValidPort ( string ):
    if string in PWM:
        return PWM [ string ] 
    return False


''' 
 Name:          isValidDC
 Parameters:    string
 Output:        boolean, True - if it is a valid input. 	
 		False - if it is not a valid input
 Description:	Check if the input is a valid number 
'''
def isValidDC ( string ):
    try:
        float ( string )
        return True
    except:

        return False

'''
 Name:          turnOff
 Parameters:    number
 Output:        None
 Description:   Turn off the output
'''
def turnOff ( port ):
    OFF = 0;
    p = m.Gpio ( port )
    p.dir ( m.DIR_OUT )
    p.write ( OFF )

# main 
def main ( argv ):
    if len ( sys.argv ) < 3:
        print ( "Usage: python " + sys.argv [ 0 ] +  " <port>" + " <duty_cycle>" )
        print ( "<port>: P0 | P1 | P2 | P3" )
        print ( "<duty_cycle>: 0.0 - 100.0" )
        sys.exit ()

# check if it is a valid  port
    p = isValidPort ( sys.argv [ 1 ] )
    if p  == False:
        print ( "Invalid port...." )
        print ( "<port>, must be: P0 | P1 | P2 | P3" )
        sys.exit ()

# check if it is a valid duty cycle
    if isValidDC ( sys.argv [ 2 ] ) == False:
        print ( "Invalid argument...." )
        print ( "<duty cycle>, must be between: 0.0 - 100.0" )
        sys.exit ()

# convert the input argument to floating point
# and check if it is in the valid interval
    value = float ( sys.argv [ 2 ] );
    if value < 0.0 or value > 100.0:
        print ( "<duty cycle>, must be between: 0.0 - 100.0" )
        sys.exit ()

    PIN_PORT = p
    out = m.Pwm ( PIN_PORT )
    out.period_us ( T )
    out.enable ( True )
    out.write ( value / 100.0 )

    print ( "MRAA Version: " + m.getVersion () )
    print ( "Platform: " + m.getPlatformName () )
    print ( "PWM: " + sys.argv [ 1 ] )
    print ( "Port Number: " +  str ( PIN_PORT ) )
    print ( "Period: " + str ( T * 1.0e-6 ) + " sec" )
    print ( "Frequency: " + str ( 1.0e6 / T ) + " Hz" )
    print ( "Percentage of PWM: "),
    print ( "{0:.2f}".format ( round ( 100 *  out.read (), 2 ) ) )

    c = raw_input ( "Press \"Enter\" to finish." )
    turnOff ( PIN_PORT )

if __name__ == "__main__":
    main ( sys.argv [ 1: ] )
