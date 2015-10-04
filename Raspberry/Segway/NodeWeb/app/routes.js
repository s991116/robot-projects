var Robot = require('./models/robot');
var RobotWrapper = require('../../NodeJSModule/robot');

function getRobot(res){
	res.json(Robot);
};

module.exports = function(app) {

	// api ---------------------------------------------------------------------
	// get Robot
	app.get('/api/robot', function(req, res) {
		getRobot(res);
	});

	// Set Robot state and send back Robot
	app.post('/api/robot', function(req, res) {
		Robot.enabled = !(Robot.enabled);
		if(Robot.enabled)
			RobotWrapper.BalanceEnabled(1);
		else
			RobotWrapper.BalanceEnabled(0);
		getRobot(res);
	});

	// application -------------------------------------------------------------
	app.get('*', function(req, res) {
		res.sendfile('./public/index.html'); // load the single view file (angular will handle the page changes on the front-end)
	});
};