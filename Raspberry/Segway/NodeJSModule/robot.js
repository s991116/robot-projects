var robot = require('bindings')('robot');

var obj = new robot.RobotWrapper();
obj.setvalue(42)
console.log(obj.getvalue());
obj.setvalue(2)
console.log(obj.getvalue());