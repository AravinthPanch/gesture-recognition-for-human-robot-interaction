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
			websocket.send("CC");
		};

		websocket.onclose = function (e) {
			console.log("Websocket Closed")
		};

		websocket.onmessage = function (e) {
			app.skeletonBuffer = JSON.parse(e.data);
			$('#consoleBox').prepend("<div class='log'>" + e.data + "</div>");
			updateGestureBox();
		};

		websocket.onerror = function (e) {
			console.log("Websocket Error")
		};
	}

	function updateGestureBox() {
		var timeOut = 1000;
		if ('GESTURE' in app.skeletonBuffer) {
			if (app.skeletonBuffer.GESTURE != "WAVE") {
				timeOut = 2000;
			}

			$('#gBox').text(app.skeletonBuffer.GESTURE);
			var timer = setTimeout(function () {
				$('#gBox').text("")
			}, timeOut);
		}

		if ('INFO' in app.skeletonBuffer) {
			$('#gestureBox').text(app.skeletonBuffer.INFO);
			var timer = setTimeout(function () {
				$('#gestureBox').text("")
			}, timeOut);
		}

		if ('TIMER' in app.skeletonBuffer) {
			$('#gestureBox').text(app.skeletonBuffer.TIMER);
		}
	}

	return {
		init: init
	}
});