module.exports = function(communication) {
    var debug = require('debug')('head');
    var serialCommands = require('./serialCommands');
    var navigationData = 0;

    let percantageRotationToByte = (percentageRotation) => {
        var value = (percentageRotation+100)*(180/200);
        return Math.round(Math.max(0, Math.min(value,180)));
    }

    let move = (vertical, horizontal) => {
        communication.sendData(serialCommands.CMD_SET_SERVO_1_POSITION, percantageRotationToByte(vertical));
        communication.sendData(serialCommands.CMD_SET_SERVO_2_POSITION, percantageRotationToByte(horizontal));
    }

    return{
        move: move,
    }
}