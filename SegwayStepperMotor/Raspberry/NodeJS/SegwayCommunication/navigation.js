module.exports = function(communication) {
    var debug = require('debug')('navigation');
    var serialCommands = require('./serialCommands');
    var navigationData = 0;

    const forwardBackardsData = {
        '-1': 0b00001000,
         '0': 0b00000000,
         '1': 0b00000100,         
    };

    const leftRightData = {
        '-1': 0b00000001,
         '0': 0b00000000,
         '1': 0b00000010,         
    };

    let sendNavigation = () => {
        if(navigationData !== 0) {
            debug("Send navigation automatic:" + navigationData);
            communication.sendData(0x11,navigationData);
        }
    }

    let navigate = (forwardBackwards, side) => {
        navigationData = forwardBackardsData[forwardBackwards] | leftRightData[side];
        debug("Send navigation moved:" + navigationData);
        communication.sendData(0x11,navigationData);
    }

    setInterval(sendNavigation, 100);

    let setPidSetting = (pValue, iValue, dValue, balancingLevel, deadBandLevel) => {
        communication.sendData(serialCommands.CMD_SET_PID_P_LEVEL, pValue * 4);
        communication.sendData(serialCommands.CMD_SET_PID_I_LEVEL, iValue * 4);
        communication.sendData(serialCommands.CMD_SET_PID_D_LEVEL, dValue * 4);
        communication.sendData(serialCommands.CMD_SET_BALANCING_LEVEL, balancingLevel * 400);
        communication.sendData(serialCommands.CMD_SET_DEADBAND_LEVEL, deadBandLevel);
        debug("PID and balance level set to: " + pValue + " , " + iValue + " , " + dValue + " , " + balancingLevel + " , " + deadBandLevel);
    }

    let getPidSetting = () => {
        return new Promise((resolve) => {
            communication.getData(serialCommands.CMD_GET_PID_P_LEVEL)
            .then( (pValue) => {
                communication.getData(serialCommands.CMD_GET_PID_I_LEVEL)
            .then( (iValue) => {
                communication.getData(serialCommands.CMD_GET_PID_D_LEVEL)
            .then( (dValue) => {
                communication.getData(serialCommands.CMD_GET_BALANCING_LEVEL)
            .then( (balancingLevel) => {
                communication.getData(serialCommands.CMD_GET_DEADBAND_LEVEL)
            .then ( (deadBandLevel) => {
                resolve([pValue/4.0, iValue/4.0, dValue/4.0, balancingLevel/400.0, deadBandLevel]);
                debug("PID and balance level received: " + pValue/4.0 + " , " + iValue/4.0 + " , " + dValue/4.0 + " , " + balancingLevel/400.0 + " , " + deadBandLevel);
            });
            });
            });
            });            
            });
        });
    }
    

    return{
        navigate: navigate,
        stop:      0,
        left:      -1,
        right:     1,
        forward:   1,
        backwards: -1,
        setPidSetting: setPidSetting,
        getPidSetting: getPidSetting,
    }
}