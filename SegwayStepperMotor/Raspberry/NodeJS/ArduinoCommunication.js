function arduino() {
  var SerialPort = require('serialport');
  var port = new SerialPort('/dev/serial0', { baudRate: 9600 });
  port.on('open', function() {
      console.log('Port open');
  });

  port.on('error', function(err) {
    console.log('Error: ', err.message);
  });
  
  function sendData(cmd,data) {
    port.write([cmd,data], function(err) {
      if (err) {
        return console.log('Error on write: ', err.message);
      }
    });
  }

  let getData = (cmd) => {
    return new Promise(
      (resolve, reject) => {
        port.write([cmd], function(err) {
          if (err) {
            reject(err);
          }
        });
        port.on('data', data => {
          response = data[0];
          resolve(response);
        })
      }
    );
  }
  return {
    sendData: sendData,
    getData: getData,
  }
}

//TEST
// let a = arduino();
// a.sendData(0x10,123)
// a.getData(0x20).then( data => {
//   console.log(data);
//   a.sendData(0x10,23);
//   a.getData(0x20).then( data => console.log(data));
// })

