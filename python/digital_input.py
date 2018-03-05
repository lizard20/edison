'''
Program: digital_input.py
Description: Read a digital input and display its value
Author: Aldo Nunez
'''

import mraa as m

# main
def main ():
    PORT = 5

    # initialize variable with a port number
    port_input = m.Gpio ( PORT )

    # set gpio direction to input
    port_input.dir ( m.DIR_IN )

    # read port value
    value  = port_input.read ()

    print ( "Input port %d: %d" % (  PORT , value ) )

if __name__ == "__main__":
    main ()
