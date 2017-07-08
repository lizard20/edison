// Program: digital_input.js
// Description: Reads a digital input and displays its value
// Author: Aldo Nunez

const PORT = 5;

var m = require ( 'mraa' );

// initialize variable with a port number
var  port_input = new m.Gpio ( PORT );

// sets the gpio direction
port_input.dir ( m.DIR_IN );

// Reads the digital value
var value = port_input.read ();

console.log ( "Input port " + PORT + ": " + value );

delete ( port_input );