'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 17/06/15.
 * Contributors:
 */


var osc = require('node-osc');

var client = new osc.Client('127.0.0.1', 5000);

var data = [-452.148,389.755,1847.94,456.911,390.352,1869.7];

setInterval(function () {
	client.send('/Data', data, function () {
		console.log("Sent")
	});
}, 5000);


