'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 31/05/15.
 * Contributors:
 */


var dgram = require('dgram');
var socket = dgram.createSocket('udp4');

var testMessage = "[hello world] pid: " + process.pid;
var multicastAddress = '239.255.0.1';
var multicastPort = 50006;


socket.bind(multicastPort, '0.0.0.0', function () {
	socket.addMembership(multicastAddress);
});

socket.on("listening", function () {
	console.log("Listening")
});

socket.on("message", function (data, rinfo) {
	console.log("Message received from ", rinfo.address, " : ", data.toString());
});