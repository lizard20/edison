// Program: digital_input.js
// Description: Reads a digital input and displays its value
// Author: Aldo Nunez

const PIN_INPUT = 5;					

var m = require ( 'mraa' ); 	
var  gpio = new m.Gpio ( PIN_INPUT ); //  
gpio.dir ( m.DIR_IN ); 			// sets the gpio direction
var input = gpio.read ();   // Reads the digital value

console.log ( 'MRAA Version: ' + m.getVersion () );
console.log ( 'Platform: ' + m.getPlatformName () );
console.log ( "input_pin_" + input + ": " + input );








