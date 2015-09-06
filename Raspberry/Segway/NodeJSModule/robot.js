var robot = require('bindings')('robot');

var obj = new robot.RobotWrapper();
obj.setvalue(0)
console.log(obj.getvalue());
