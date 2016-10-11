''' 
 Name: pwm.py
 Description: Generate a PWM output. The user enters 
              the percentage of  duty cycle
 Author: Aldo Nunez
'''

import mraa as m
import sys

PWM = { 'PWM0':3, 'PWM1':5, 'PWM2':6, 'PWM3':9 }
T = 20000    # Period: 20000 usec ~ 50 Hz

''' 
 Name:         isValid
 Parameters:   string
 Output: 	boolean, True - if it is a valid input. 	
 		False - if it is not a valid input
 Description:	Check if the input is a valid number 
'''
def isValid ( string ):
    try:
        float (string)
        return True
    except:

        return False
        
if len ( sys.argv ) < 2:
    print ( "Usage: "+ sys.argv [ 0 ] + " <number>" )
    sys.exit ()

if isValid ( sys.argv [ 1 ] ) == False:
    print ( "Invalid argument...." )
    print ( "Argument must be a number between: 0.0 - 100.0" )
    sys.exit ()

value = float ( sys.argv [ 1 ] );
if value < 0.0 or value > 100.0:
    print ( "<number> must be between: 0.0 - 100.0" )
    sys.exit ()
	     
PIN_PORT = PWM [ 'PWM0' ]
out = m.Pwm ( PIN_PORT )
out.period_us ( T )
out.enable ( True )
out.write ( value / 100.0 )

print ( "MRAA Version: " + m.getVersion () )
print ( "Platform: " + m.getPlatformName () )
print ( "Port Number: " +  str ( PIN_PORT ) )
print ( "Period: " + str ( T * 1.0e-6 ) + " sec" )
print ( "Frequency: " + str ( 1.0e6 / T ) + " Hz" )
print ( "Percentage of PWM: "),
print ( "{0:.2f}".format ( round ( 100 *  out.read (), 2 ) ) )
c = raw_input ( "Press \"Enter\" to finish." )
