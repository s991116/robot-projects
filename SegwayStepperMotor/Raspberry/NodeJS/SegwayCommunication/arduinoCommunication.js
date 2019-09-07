function arduino() {
  var chalk = require('chalk');
  var debug = require('debug')('app');
  
  var SerialPort = require('serialport');
  var port = new SerialPort('/dev/serial0', { baudRate: 9600 });
  port.on('open', function() {
      debug(chalk.green('Port open'));
  });

  port.on('error', function(err) {
    debug(chalk.red('Error: ', err.message));
  });
  
  function sendData(cmd,data) {
    port.write([cmd,data], function(err) {
      if (err) {
        return debug(chalk.red('Error: ', err.message));
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