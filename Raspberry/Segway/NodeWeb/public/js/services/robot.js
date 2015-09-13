angular.module('robotService', [])

	// super simple service
	// each function returns a promise object 
	.factory('Robot', ['$http',function($http) {
		return {
			get : function() {
				return $http.get('/api/robot');
			},
			create : function(data) {
				return $http.post('/api/robot', data);
			},
		}
	}]);