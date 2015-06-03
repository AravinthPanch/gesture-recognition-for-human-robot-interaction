'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */

app.skeletonBuffer = {};

define(function () {
	var websocket = {},
		websocketUri = "ws://localhost:5008";

	function init() {
		websocket = new WebSocket(websocketUri);

		websocket.onopen = function (e) {
			console.log("Websocket Opened");
			websocket.send("HRI:Control Center");
		};

		websocket.onclose = function (e) {
			console.log("Websocket Closed")
		};

		websocket.onmessage = function (e) {
			app.skeletonBuffer = JSON.parse(e.data);
			$('#consoleBox').prepend("<div class='log'>" + e.data + "</div>");
		};

		websocket.onerror = function (e) {
			console.log("Websocket Error")
		};
	}

	return {
		init: init
	}
});