'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 02/01/15.
 * Contributors:
 */


/**
 * Global Variable to hold app
 */

if (typeof app === 'undefined') {
	var app = {};
}

/**
 * Require JS configuration and start the APP
 */
require.config({
	paths: {
		socketio: 'lib/socket.io',
		jquery: 'lib/jquery.min',
		three: 'lib/three.min',
		trackBallControl: 'lib/TrackballControls',
		stats: 'lib/stats.min',
		underscore: 'lib/underscore.min',
		semantic: 'css/ui/semantic',
		gui: 'lib/dat.gui.min',
		font: 'css/helvetiker_regular.typeface'

	},

	shim: {
		'three': {exports: 'THREE'},
		'trackBallControl': {deps: ['three'], exports: 'THREE'},
		'stats': {exports: 'Stats'},
		'font': {deps: ['three']}
	}
});

require(['js/view', 'js/store'], function (view, store) {
	view.init();
	store.init();
});



