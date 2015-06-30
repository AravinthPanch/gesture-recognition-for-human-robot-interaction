'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 17/06/15.
 * Contributors:
 */


var osc = require('node-osc');

var client = new osc.Client('127.0.0.1', 5000);

var classLabel = 2;

var data = require('../../../../data/test/json/' + classLabel + '.js');

var i = 0;

setInterval(function () {

	if ('RIGHT' in data.handData[i] && 'LEFT' in data.handData[i]) {
		var left = data.handData[i].LEFT.map(Number);
		var right = data.handData[i].RIGHT.map(Number);
		var output = left.concat(right);

		client.send('/Data', output, function () {
			console.log(output)
		});
	}

	i++;

}, 30);


