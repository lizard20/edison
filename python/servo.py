'''
 Program: servo.py
 Description: Generates a PWM signal to control a servo
 Author: Aldo Nunez
'''
import sys
import mraa as m

PORT = 3

T = 20000           # Period: 20 msec; f = 50 Hz
CLKWISE = 1.0e-3
CCLKWISE = 2.0e-3

'''
 Program: turnServo
 Parameters: p	- Reference to pwm
             t  - Period in micro seconds
             pw - Pulse width
 Output:     None
 Description: Enable, set the period and send
            the command to generate pwm signal 				
'''
def turn_servo ( p, t, d ):
    pwm.period_us ( t )
    pwm.enable ( True ) 
    pwm.pulsewidth ( d )
    return;

try:
    n =  sys.argv [ 1 ]
except:
    print ( "<Usage>: " + sys.argv [ 0 ] + " <DIR>" )
    print ( "<DIR>: CW or CCW")
    sys.exit()

pwm = m.Pwm ( PORT )
pwm.period_us ( T )

if sys.argv [ 1 ] == 'CW':
    turn_servo ( pwm, T, CLKWISE )
elif sys.argv [ 1 ] == 'CCW':
    turn_servo ( pwm, T, CCLKWISE )
else:
    print ( "<DIR>: CW or CCW")
    sys.exit ()

print ( "MRAA Version: " + m.getVersion () )
print ( "Platform: " + m.getPlatformName () )
print ( "Port Number: " +  str ( PORT) )

c = raw_input ( "Press \"Enter\" to finish." )
