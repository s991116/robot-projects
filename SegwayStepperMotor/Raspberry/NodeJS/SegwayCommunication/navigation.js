module.exports = function(communication) {

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

    let navigate = (forwardBackwards, side) => {
        let navigationData = forwardBackardsData[forwardBackwards] | leftRightData[side];
        communication.sendData(0x11,navigationData);
    }
    
    return{
        navigate: navigate,
        stop:      0,
        left:      -1,
        right:     1,
        forward:   1,
        backwards: -1,
    }
}