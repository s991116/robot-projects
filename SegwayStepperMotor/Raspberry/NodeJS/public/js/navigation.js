var socket = io();

var posX, posY;
var navigationJoystick = nipplejs.create({
    zone: document.getElementById('navigation_joystick'),
    mode: 'static',
    position: {left: '50%', top: '50%'},
    color: 'red'
});

var headJoystick = nipplejs.create({
    zone: document.getElementById('head_joystick'),
    mode: 'static',
    position: {left: '50%', top: '50%'},
    color: 'blue'
});


navigationJoystick.on('move', (evt, data) => {
    var angle = data.angle.radian;
    var distance = data.distance/50.0;
    var positionX = distance * Math.cos(angle);
    var positionY = distance * Math.sin(angle);
    var x = Math.round((3/2)*positionX);
    var y = Math.round((3/2)*positionY);
    if(x !== posX || y !== posY) {
        posX = x;
        posY = y;
        socket.emit('navigation', [posY, posX]);
    }
});

navigationJoystick.on('end', () => {
        socket.emit('navigation', [0, 0]);
});

headJoystick.on('move', (evt, data) => {
    var angle = data.angle.radian;
    var distance = data.distance/50.0;
    var positionX = distance * Math.cos(angle);
    var positionY = distance * Math.sin(angle);
    var x = Math.round(100*positionX);
    var y = Math.round(100*positionY);
    if(x !== posX || y !== posY) {
        posX = x;
        posY = y;
        socket.emit('head', [posY, posX]);
    }
});

headJoystick.on('end', () => {
        socket.emit('head', [0, 0]);
});

function buttonClicked(){
    var pValue = document.getElementById("pValue").value;
    var iValue = document.getElementById("iValue").value;
    var dValue = document.getElementById("dValue").value;
  socket.emit('PIDUpdate', [pValue,iValue,dValue]);
};

function buttonTestCommunicationClicked(){
    socket.emit('TestCommunication');
    socket.once('TestResult', (testResult) => {
        if(testResult) {
            alert("Communication OK");
        }
        else {
            alert("Communication failed!");
        }
    }); 
};

var canvas = document.getElementById('video-canvas');
var url = 'ws://'+document.location.hostname+':8082/';
var player = new JSMpeg.Player(url, {canvas: canvas});

let toggleVideo = () => {
    socket.emit('CameraToggle');
}
canvas.addEventListener('click', toggleVideo, false);
 