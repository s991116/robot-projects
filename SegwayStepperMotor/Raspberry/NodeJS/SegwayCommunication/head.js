module.exports = async function(communication) {
    var debug = require('debug')('head');
    var serialCommands = require('./serialCommands');
    
    var horizontalPosition = await communication.getData(serialCommands.CMD_GET_SERVO_1_POSITION);
    var verticalPosition   = await communication.getData(serialCommands.CMD_GET_SERVO_2_POSITION);

    var horizontalMin = await communication.getData(serialCommands.CMD_GET_SERVO_1_MIN);
    var horizontalMax = await communication.getData(serialCommands.CMD_GET_SERVO_1_MAX);

    var verticalMin = await communication.getData(serialCommands.CMD_GET_SERVO_2_MIN);
    var verticalMax = await communication.getData(serialCommands.CMD_GET_SERVO_2_MAX);

    var verticalMove = 0;
    var horizontalMove = 0;

    var previusHorizontalAngle = -1;
    var previusVerticalAngle = -1;

    let percantageVerticalRotationToByte = (percentageRotation) => {
        var value = verticalMin + (percentageRotation+100)/200 * (verticalMax-verticalMin);
        return Math.round(Math.max(0, Math.min(value,180)));
    }

    let percantageHorizontalRotationToByte = (percentageRotation) => {
        var value = horizontalMin + (percentageRotation+100)/200 * (horizontalMax-horizontalMin);
        return Math.round(Math.max(0, Math.min(value,180)));
    }

    let updatePosition = () => {
        verticalPosition += -verticalMove/40.0;
        verticalPosition = Math.max(-100, Math.min(100, verticalPosition));
        horizontalPosition += horizontalMove/50.0;
        horizontalPosition = Math.max(-100, Math.min(100, horizontalPosition));
        
        var verticalAngle = percantageVerticalRotationToByte(verticalPosition);
        var horizontalAngle = percantageHorizontalRotationToByte(horizontalPosition);
        
        if(previusVerticalAngle !== verticalAngle) {
            debug("Update head position to " + verticalPosition + " , " + horizontalPosition);
            communication.sendData(serialCommands.CMD_SET_SERVO_2_POSITION, verticalAngle);
            previusVerticalAngle = verticalAngle;
        }

        if(previusHorizontalAngle !== horizontalAngle) {
            debug("Update head angle to " + verticalAngle + " , " + horizontalAngle);
            communication.sendData(serialCommands.CMD_SET_SERVO_1_POSITION, horizontalAngle);
            previusHorizontalAngle = horizontalAngle;
        }
    }

    updatePosition();
    setInterval(updatePosition, 100);

    let move = (vertical, horizontal) => {
        verticalMove = vertical;
        horizontalMove = horizontal;
        updatePosition();
    }

    return{
        move: move,
    }
}