var m = require('mraa'); //IO Library
var app = require('express')(); //Express Library
var server = require('http').Server(app); //Create HTTP instance

var io = require('socket.io')(server); //Socket.IO Library

var ledState = 1; //set default LED state
var PIN = 13;

var myLed = new m.Gpio ( PIN ); //LED hooked up to digital pin 13
myLed.dir ( m.DIR_OUT ); //set the gpio direction to output

app.get('/', function ( req, res )
{                  
	res.sendfile ( __dirname + '/index.html' ); //serve the static html file
	//res.sendFile ( path.join ( __dirname, '../index.html' ) ); //serve the static html file
//	console.log ( path.join ( __dirname, '..', '/index.html' ) ); //serve the static html file
	//console.log (path.join ( __dirname, '/../', 'index.html' ) ); //serve the static html file
});                                                 

var s = 0;
var blink_st = 0;
toggleInterval = 200;
io.on ( 'connection', function ( socket )
{
	socket.on ('changeState', function () 
	{ //on incoming websocket message...
		if ( blink_st == 0)
			toggle ();
	});
	socket.on ('blink', function () 
	{ //on incoming websocket message...
		blink_st = ~blink_st;
		if ( s == 0 )
		{
			s = 1;
		}
		else
		{
			s = 0;
		}
		blink();
	});

});                                                   

server.listen(3000); //run on port 3000
function toggle ()
{  
	myLed.write ( ledState ); //write the LED state
	ledState = 1 - ledState; //toggle LED state
}  

function blink ()
{                                                                              
		myLed.write ( ledState ); //write the LED state
		ledState = 1 - ledState; //toggle LED state
		if (s == 1)
			setTimeout (blink, toggleInterval  ); //recursively toggle pin state with timeout set to blink interval
		else
			myLed.write ( 0 ); //write the LED state
}  



