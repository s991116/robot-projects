module.exports = async function(port) {
  var chalk = require('chalk');
  var debug = require('debug')('app');
  var serialCommands = require('./serialCommands');

  if(port == undefined) {
    var SerialPort = require('serialport');
    var port = new SerialPort('/dev/serial0', { baudRate: 115200 });
  }

  let sendData = (cmd,data) => {
    cmd = Math.round(cmd) + Math.round(serialCommands.CMD_SET_TYPE);
    data = Math.round(data);
    debug(chalk.green("Send cmd:" + cmd + " , data:" + data));
    port.write([cmd,data], (err) => {
      if (err) {
        return debug(chalk.red('Error: ', err.message));
      }
    });
  }

  let sendNavigation = (navigation) => {
    cmd = Math.round(navigation) + Math.round(serialCommands.CMD_NAVIGATION_TYPE);
    debug(chalk.green("Send navigation:" + cmd));
    port.write([cmd], (err) => {
      if (err) {
        return debug(chalk.red('Error: ', err.message));
      }
    });
  }

  let getData = (cmd) => {
    cmd = Math.round(cmd) + Math.round(serialCommands.CMD_GET_TYPE);
    debug(chalk.green("Get cmd:" + cmd));
    return new Promise(
      (resolve, reject) => {
        port.write([cmd], (err) => {
          if (err) {
            reject(err);
          }
        });
        port.on('data', data => {
          response = data[0];
          debug(chalk.green("Received data:" + response));
          resolve(response);
        })
      }
    );
  }

  var serialCom =  new Promise(
    (resolve, reject) => {
        port.on('open', function() {
            debug(chalk.green('Port open'));
            resolve({
              sendData: sendData,
              getData: getData,
              sendNavigation: sendNavigation,      
            })
        });
    
        port.on('error', function(err) {
          debug(chalk.red('Error: ', err.message));
          reject(err);
        });
    }
  )

  return serialCom;
}