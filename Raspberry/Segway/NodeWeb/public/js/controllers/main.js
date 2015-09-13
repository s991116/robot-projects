angular.module('robotController', [])

	// inject the Robot service factory into our controller
	.controller('mainController', ['$scope','$http','Robot', function($scope, $http, Robot) {
		$scope.formData = {};
		$scope.loading = true;

		// GET =====================================================================
		// when landing on the page, get Robot state
		Robot.get()
			.success(function(data) {
				$scope.robot = data;
				$scope.loading = false;
			});

		// CREATE ==================================================================
		// when submitting the add form, send the text to the node API
		$scope.enable = function() {
			// call the create function from our service (returns a promise object)
			Robot.create($scope.formData)
	
			// if successful creation, update robot state
			.success(function(data) {
				$scope.loading = false;
				$scope.formData = {}; // clear the form so our user is ready to enter another
				$scope.robot = data;
			});
		};
	}]);