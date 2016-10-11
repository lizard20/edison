'''
Program: digital_input.py
 Description: Read digital input and display its value
 Author: Aldo Nunez
'''

import mraa as m

PIN_INPUT = 5
pin_input = m.Gpio ( PIN_INPUT )
pin_input.dir ( m.DIR_IN )

value  = pin_input.read ()

print ( "MRAA Version: " +  m.getVersion () );
print ( "Platform: " +  m.getPlatformName () );
print ( "Input pin_" + str ( PIN_INPUT ) + ": " + str ( value ) )
