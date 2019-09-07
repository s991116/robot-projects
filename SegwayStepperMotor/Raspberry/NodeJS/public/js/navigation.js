var socket = io();

var posX, posY;
var joystick = nipplejs.create({
    zone: document.getElementById('zone_joystick'),
    mode: 'static',
    position: {left: '50%', top: '50%'},
    color: 'red'
});

joystick.on('move', (evt, data) => {
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