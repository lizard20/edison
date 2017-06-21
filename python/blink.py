'''
 Program: blink.py
 Description: blink LED
 Author: Aldo Nunez
'''
import mraa as m
import time
import sys


# STATES
OFF = 0 
ON = 1

# 13 ~ led DS2
LED = 13    

# time
T =  1.0    # 1.0 ~ 1 sec 

def main():
    led = m.Gpio ( LED )
    led.dir ( m.DIR_OUT )
    print ( "To finish press: Ctrl + c" )
    try:
        while True:
            led.write ( ON )
            time.sleep ( T )
            led.write ( OFF )
            time.sleep ( T )
    except KeyboardInterrupt:
        led.write ( OFF )
        print ( "blink is closing..." )
        sys.exit ( 0 )

if __name__ == "__main__":
    main ()
