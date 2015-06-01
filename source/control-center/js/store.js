'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

app.skeletonBuffer = {};

define(['socketio'], function (socketio) {

	var websocketUri = "ws://localhost:5008";
	var websocket = new WebSocket(websocketUri);

	websocket.onopen = function (e) {
		onOpen(e)
	};
	websocket.onclose = function (e) {
		onClose(e)
	};
	websocket.onmessage = function (e) {
		onMessage(e)
	};
	websocket.onerror = function (e) {
		onError(e)
	};

	function onOpen(e) {
		console.log("Open");
		websocket.send("HRI:Control Center");
	}

	function onClose(e) {
		console.log("Websocket Closed")
	}

	function onMessage(e) {
		app.skeletonBuffer = JSON.parse(e.data)
	}

	function onError(e) {
		console.error(e.data)
	}

	function init() {
		console.log("init")
	}

	return {
		init: init
	}
});