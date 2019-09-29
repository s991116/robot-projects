module.exports = function(communication) {
    var debug = require('debug')('head');
    var serialCommands = require('./serialCommands');
    var verticalPosition   = 0;
    var horizontalPosition = 0;
    var verticalMove = 0;
    var horizontalMove = 0;

    let percantageRotationToByte = (percentageRotation) => {
        var value = (percentageRotation+100)*(180/200);
        return Math.round(Math.max(0, Math.min(value,180)));
    }

    let updatePosition = () => {
        verticalPosition += -verticalMove/40.0;
        verticalPosition = Math.max(-100, Math.min(100, verticalPosition));
        horizontalPosition += horizontalMove/50.0;
        horizontalPosition = Math.max(-100, Math.min(100, horizontalPosition));
        var verticalAngle = percantageRotationToByte(verticalPosition);
        var horizontalAngle = percantageRotationToByte(horizontalPosition);
        debug("Update head position to " + verticalAngle + " , " + horizontalAngle);
        communication.sendData(serialCommands.CMD_SET_SERVO_2_POSITION, verticalAngle);
        communication.sendData(serialCommands.CMD_SET_SERVO_1_POSITION, horizontalAngle);
    }

    updatePosition();
    //setInterval(updatePosition, 100);

    let move = (vertical, horizontal) => {
        verticalMove = vertical;
        horizontalMove = horizontal;
        updatePosition();
    }

    return{
        move: move,
    }
}