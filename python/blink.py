'''
 Program: blink.py
 Description: blink LED
 Author: Aldo Nunez
'''
import mraa as m
import time

# STATES
OFF = 0 
ON = 1

# 13 ~ led DS2
LED = 13    

# time
T =  1.0    # 1.0 ~ 1 sec 

led = m.Gpio ( LED )
led.dir ( m.DIR_OUT )

while True:
    led.write ( ON )
    time.sleep ( T )
    led.write ( OFF )
    time.sleep ( T )
