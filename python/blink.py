'''
 Program: blink.py
 Description: blink LED
 Author: Aldo Nunez
'''
import mraa as m
import time
import sys

# main
def main ():
    led = m.Gpio ( 13 )
    led.dir ( m.DIR_OUT )

    while True:
        led.write ( 1 )
        time.sleep ( 1 )
        led.write ( 0 )
        time.sleep ( 1 )

if __name__ == "__main__":
    main ()
