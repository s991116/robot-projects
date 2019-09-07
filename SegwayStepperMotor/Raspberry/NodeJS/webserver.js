var express = require('express');
var chalk = require('chalk');
var debug = require('debug')('app');
var morgan = require('morgan');
var path = require('path');
var http = require('http');
var io = require('socket.io');//(express) //require socket.io module and pass the http object (server)

var arduinoCom = require('./SegwayCommunication/arduinoCommunication')();
var navigation = require('./SegwayCommunication/navigation')(arduinoCom);

var app = express();
var httpApp = http.Server(app);
var ioApp = io(httpApp);

app.use(morgan('tiny'));

app.use(express.static(path.join(__dirname,'public')));
app.use('/css',express.static(path.join(__dirname,'/node_modules/bootstrap/dist/css')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/bootstrap/dist/js')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/jquery/dist')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/nipplejs/dist')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/popper.js/dist')));
app.use('/js',express.static(path.join(__dirname,'/node_modules/socket.io-client/dist')));

app.get('/', function(req,res){
  res.sendFile(path.join(__dirname,'public/index.html'));
})
console.log(arduinoCom);
ioApp.sockets.on('connection', function (socket) {// WebSocket Connection
  debug(chalk.green('Client connected.'));
  socket.on('navigation', (data) => {
    navigation.navigate(data[0], data[1]);
  });
  socket.on('disconnect', (data) => {
    navigation.navigate(0,0);
  });
});

var server = httpApp.listen(8080, function() {
  debug(`listening on port ${chalk.green(server.address().port)}`);
})