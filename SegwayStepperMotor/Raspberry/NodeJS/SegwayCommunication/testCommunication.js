module.exports = function(communication) {
    var serialCommands = require('./serialCommands');

    var promise = (testValue) => {
        communication.sendData(serialCommands.CMD_SET_TEST_VALUE, testValue);
        return communication.getData(serialCommands.CMD_GET_TEST_VALUE);
    }

    testCommunication = () => {        
        return new Promise((resolve) => {
            promise(1).then((value1) => {
                promise(2).then((value2) => {
                    resolve(value1==1 && value2==2)
                })
            })
        })
    }

    return {
        testCommunication: testCommunication
    }
}