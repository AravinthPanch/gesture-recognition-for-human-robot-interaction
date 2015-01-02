'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

app.skeletonBuffer = {};

define(function (require) {
	var socket = require('socketio');
	socket = socket.connect();

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