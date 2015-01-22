'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

var express = require('express'),
	app = express(),
	server = require('http').createServer(app),
	io = require('socket.io')(server),
	logger = require('log4js').getLogger();


// Sever configuration
app.set('port', process.env.PORT || 5007);
app.use(express.static(__dirname, '/public'));


// Socket interface to the frontend
io.on('connection', function (socket) {
	socket.on('init', function () {
		logger.info('Client Connected');
		sendUdpData(socket);
	});
});


// Server starting
server.listen(app.get('port'), function () {
	logger.info('Server is started');
	logger.info('App is started at http://localhost:%d', app.get('port'));
});


// Stream UDP to Frontend
function sendUdpData(socket) {
	var server_port = 5005;
	var client_port = 5006;
	var server_host = 'nao6.local';
	var client_host = '127.0.0.1';

	var dgram = require('dgram');
	var server = dgram.createSocket('udp4');

	var message = new Buffer('01');

	server.send(message, 0, message.length, server_port, server_host, function (err, bytes) {
		if (err) throw err;
		logger.info('UDP message sent to ' + server_host + ':' + server_port);
	});

	server.on('listening', function () {
		var address = server.address();
		logger.info('UDP Server listening on ' + address.address + ":" + address.port);
	});

	server.on('message', function (message, remote) {
		logger.debug(remote.address + ':' + remote.port + ' - ' + message);
		socket.emit('skeleton', JSON.parse(message));
	});

	//server.bind(client_port, client_host);
}