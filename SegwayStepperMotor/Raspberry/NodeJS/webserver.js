var express = require('express');
var chalk = require('chalk');
var debug = require('debug')('app');
var morgan = require('morgan');
var path = require('path');

var app = express();
app.use(morgan('tiny'));

app.use(express.static(path.join(__dirname,'public')));
app.use('/css',express.static(path.join(__dirname,'/node_modules/bootstrap/dist/css')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/bootstrap/dist/js')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/jquery/dist')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/nipplejs/dist')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/popper.js/dist')));

app.get('/', function(req,res){
  res.sendFile(path.join(__dirname,'public/index.html'));
})

app.listen(8080, function() {
  debug(`listening on port ${chalk.green('3000')}`);
})

/*
var io = require('socket.io')(http) //require socket.io module and pass the http object (server)

io.sockets.on('connection', function (socket) {// WebSocket Connection
  var lightvalue = 0; //static variable for current status
  socket.on('light', function(data) { //get light switch status from client
    lightvalue = data;
    if (lightvalue) {
      console.log(lightvalue); //turn LED on or off, for now we will just show it in console.log
    }
  });
});
*/