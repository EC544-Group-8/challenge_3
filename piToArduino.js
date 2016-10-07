var SerialPort = require("serialport");
var express = require('express');
var app = express();
var http = require('http').Server(app);
var portName = process.argv[2],
portConfig = {
	baudRate: 115200,
	parser: SerialPort.parsers.readline("\n")
};
var sp;
sp = new SerialPort.SerialPort(portName, portConfig);

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res){
  res.sendfile('index.html');
});



// --------- DEFINE AJAX POST REQUESTS HERE --------- //
// For changing the led on
app.get('/led_on/red', function(req, res){
  sp.write('A');
});

// For changing the led on
app.get('/led_off/red', function(req, res){
  sp.write('B');
});

// For changing the led on
app.get('/led_on/green', function(req, res){
  sp.write('C');
});

// For changing the led on
app.get('/led_off/green', function(req, res){
  sp.write('D');
});

// For changing the led on
app.get('/led_on/blue', function(req, res){
  sp.write('E');
});

// For changing the led on
app.get('/led_off/blue', function(req, res){
  sp.write('F');
});

// For changing the led on
app.get('/led_on/yellow', function(req, res){
  sp.write('G');
});

// For changing the led on
app.get('/led_off/yellow', function(req, res){
  sp.write('H');
});

// For getting the status 
app.get('/get_status/red', function(req, res){
  sp.write('I');
});

// For getting the status 
app.get('/get_status/green', function(req, res){
  sp.write('J');
});

// For getting the status 
app.get('/get_status/blue', function(req, res){
  sp.write('K');
});

// For getting the status 
app.get('/get_status/yellow', function(req, res){
  sp.write('L');
});



// --------- END AJAX POST REQUESTS HERE --------- //




http.listen(3000, function(){
  console.log('listening on *:3000');
});

sp.on("open", function () {
  console.log('open');
  sp.on('data', function(data) {
    alert('data received: ' + data);
  });
});

