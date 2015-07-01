'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 30/06/15.
 * Contributors:
 */


var classLabel = 3;

var csv = require('fast-csv'),
	fs = require('fs'),
	data = require('../../../../data/test/json/' + classLabel + '.js');

var csvStream = csv.createWriteStream({headers: true}),
	writableStream = fs.createWriteStream(classLabel + ".csv");

writableStream.on("finish", function () {
	console.log("DONE!");
});

csvStream.pipe(writableStream);

for (var i = 0; i < data.handData.length; i++) {
	if ('RIGHT' in data.handData[i] && 'LEFT' in data.handData[i]) {
		var left = data.handData[i].LEFT;
		var right = data.handData[i].RIGHT;
		csvStream.write(
			{
				class: classLabel,
				leftX: left[0],
				leftY: left[1],
				leftZ: left[2],
				rightX: right[0],
				rightY: right[1],
				rightZ: right[2]
			}
		);
	}
}


csvStream.end();

