'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 17/06/15.
 * Contributors:
 */


var osc = require('node-osc');

var client = new osc.Client('127.0.0.1', 5000);

var data = [-381.92, -434.746, 1741.68, 698.636, 123.435, 2027.13];

setInterval(function () {
	client.send('/Data', data, function () {
		console.log("Sent")
	});
}, 5000);

