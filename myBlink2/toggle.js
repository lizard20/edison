var m = require('mraa'); //IO Library
var app = require('express')(); //Express Library
var server = require('http').Server(app); //Create HTTP instance

var io = require('socket.io')(server); //Socket.IO Library

const STATE = { OFF: 0, ON: 1 };
const PIN = 13;

var ledState = STATE.ON; //set default LED state

var myLed = new m.Gpio ( PIN ); //LED hooked up to digital pin 13
myLed.dir ( m.DIR_OUT ); //set the gpio direction to output

app.get('/', function ( req, res )
{                  
	res.sendFile ( __dirname + '/index.html' ); //serve the static html file
});                                                 

var s = false;

toggleInterval = 200;
io.on ( 'connection', function ( socket )
{
	socket.on ('changeState', function () 
	{ //on incoming websocket message...
		if ( s == false )
			toggle ();
	});
	socket.on ('blink', function () 
	{ //on incoming websocket message...
		s = !s;
		blink ();
	});

});                                                   

server.listen ( 3000 ); //run on port 3000
function toggle ()
{   
	myLed.write ( ledState ); //write the LED state
	ledState = 1 - ledState; //toggle LED state
}  

function blink ()
{                                                                              
		myLed.write ( ledState ); //write the LED state
		ledState = 1 - ledState; //toggle LED state
		if (s == true )
			setTimeout (blink, toggleInterval  ); //recursively toggle pin state with timeout set to blink interval
		else
		{
			myLed.write ( STATE.OFF ); //write the LED state
			ledState = STATE.ON;
		}
}  



