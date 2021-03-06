'''
 Program: servo.py
 Description: Generates a PWM signal to control a servo motor
 Author: Aldo Nunez
'''
import sys
import mraa as m

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
    p.period_us ( t )
    p.enable ( True ) 
    p.pulsewidth ( d )
    return;

def main ( argv ):
    try:
        n =  sys.argv [ 1 ]
    except:
        print ( "<Usage>: " + sys.argv [ 0 ] + " <DIR>" )
        print ( "<DIR>: CW or CCW")
        sys.exit()
    
    PORT = 3
    T = 20000           # Period: 20 msec; f = 50 Hz
    CLKWISE = 1.0e-3
    CCLKWISE = 2.0e-3


    pwm = m.Pwm ( PORT )
    pwm.period_us ( T )
    turn_dir = sys.argv [ 1 ]

    if turn_dir == 'CW':
        turn_servo ( pwm, T, CLKWISE )
    elif turn_dir == 'CCW':
        turn_servo ( pwm, T, CCLKWISE )
    else:
        print ( "<Usage>: " + sys.argv [ 0 ] + " <DIR>" )
        print ( "<DIR>: CW or CCW")
        sys.exit ()

    print ( "MRAA Version: " + m.getVersion () )
    print ( "Platform: " + m.getPlatformName () )
    print ( "Port Number: " +  str ( PORT) )
    print ( "Clockwise" if turn_dir == "CW"  else "Counter clockwise" )
    c = raw_input ( "" )

if __name__ == "__main__":
    main ( sys.argv [ 1: ] )

