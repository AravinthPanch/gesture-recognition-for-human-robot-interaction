'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

app.skeletonBuffer = {};

define(['socketio'], function (socketio) {
	var socket = socketio.connect();

	function init() {
		socket.emit('init', 'udp');
		socket.on('skeleton', function (data) {
			app.skeletonBuffer = data;
		});
	}

	return {
		init: init
	}
});