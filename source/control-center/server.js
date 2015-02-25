'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

var config = require('../config/hri.json'),
	express = require('express'),
	app = express(),
	server = require('http').createServer(app),
	io = require('socket.io')(server),
	logger = require('log4js').getLogger();


// Sever configuration
app.use(express.static(__dirname, '/public'));


// Socket interface to the frontend
io.on('connection', function (socket) {
	socket.on('init', function (data) {
		switch (data) {
			case 'client':
				logger.info('Client Connected');
				break;
			case 'handTracking':
				sendUdpData(socket, '01');
				logger.info('Requested Hand Tracking');
				break;
			case 'skeletonTracking':
				sendUdpData(socket, '02');
				logger.info('Requested Skeleton Tracking');
				break;
		}
	});
});


// Server starting
server.listen(config.controlCenterPort, function () {
	logger.info('Server is started');
	logger.info('App is started at http://localhost:%d', config.controlCenterPort);
});


// Stream UDP to Frontend
function sendUdpData(socket, mode) {

	var dgram = require('dgram');
	var server = dgram.createSocket('udp4');

	var message = new Buffer(mode);

	server.send(message, 0, message.length, config.serverPort, config.serverHostName, function (err, bytes) {
		if (err) throw err;
		logger.info('UDP message sent to ' + config.serverHostName + ':' + config.serverPort);
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