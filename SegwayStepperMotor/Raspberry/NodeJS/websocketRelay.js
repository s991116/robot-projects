module.exports = function(streamSecret, streamPort, websocketPort) {
	var fs = require('fs'),
		http = require('http'),
		WebSocket = require('ws');
	var debug = require('debug')('relay');


	const recordStream = false;

	// Websocket Server
	var socketServer = new WebSocket.Server({port: websocketPort, perMessageDeflate: false});
	socketServer.connectionCount = 0;
	socketServer.on('connection', function(socket, upgradeReq) {
		socketServer.connectionCount++;
		debug(
			'New WebSocket Connection: ', 
			(upgradeReq || socket.upgradeReq).socket.remoteAddress,
			(upgradeReq || socket.upgradeReq).headers['user-agent'],
			'('+socketServer.connectionCount+' total)'
		);
		socket.on('close', function(code, message){
			socketServer.connectionCount--;
			debug(
				'Disconnected WebSocket ('+socketServer.connectionCount+' total)'
			);
		});
	});
	socketServer.broadcast = function(data) {
		socketServer.clients.forEach(function each(client) {
			if (client.readyState === WebSocket.OPEN) {
				client.send(data);
			}
		});
	};

	// HTTP Server to accept incomming MPEG-TS Stream from ffmpeg
	var streamServer = http.createServer( function(request, response) {
		var params = request.url.substr(1).split('/');

		if (params[0] !== streamSecret) {
			debug(
				'Failed Stream Connection: '+ request.socket.remoteAddress + ':' +
				request.socket.remotePort + ' - wrong secret.'
			);
			response.end();
		}

		response.connection.setTimeout(0);
		debug(
			'Stream Connected: ' + 
			request.socket.remoteAddress + ':' +
			request.socket.remotePort
		);
		request.on('data', function(data){
			socketServer.broadcast(data);
			if (request.socket.recording) {
				request.socket.recording.write(data);
			}
		});
		request.on('end',function(){
			debug('close');
			if (request.socket.recording) {
				request.socket.recording.close();
			}
		});

		// Record the stream to a local file?
		if (recordStream) {
			var path = 'recordings/' + Date.now() + '.ts';
			request.socket.recording = fs.createWriteStream(path);
		}
	}).listen(streamPort);

	debug('Listening for incomming MPEG-TS Stream on http://127.0.0.1:'+streamPort+'/<secret>');
	debug('Awaiting WebSocket connections on ws://127.0.0.1:'+websocketPort+'/');
}