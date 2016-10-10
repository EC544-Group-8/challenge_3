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

var dataRx = false;
// For getting the status 
app.get('/get_status/red', function(req, res){
  sp.write('I');
  console.log('trying to send current data: ');
  res.send(current_status);
});

// For getting the status 
app.get('/get_status/green', function(req, res){
  sp.write('J');
  res.send(current_status);
  dataRx = false;
});

// For getting the status 
app.get('/get_status/blue', function(req, res){
  sp.write('K');
  res.send(current_status);
});

// For getting the status 
app.get('/get_status/yellow', function(req, res){
  sp.write('L');
  res.send(current_status);
});


// --------- END AJAX POST REQUESTS HERE --------- //


http.listen(3000, function(){
  console.log('listening on *:3000');
});

sp.on("open", function () {
  console.log('open');
  sp.on('data', function(data) {
    console.log('data received: ');
    current_status = data;
  });
});



var current_status = '1';
// Function to extract Arduino reponse 
function read_status(datastring){
  console.log('the data sent back is: ');
  console.log(datastring);
  var data_status = parseFloat(datastring[0]);
  return data_status
}



