'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 03/01/15.
 * Contributors:
 */

var gulp = require('gulp');
var nodemon = require('gulp-nodemon');
var open = require('gulp-open');
var livereload = require('gulp-livereload');


// Start node server
gulp.task('start-server', function () {
	nodemon({
		script: 'server.js',
		options: '-e js -i js/'
	});
});


// Watch Task
gulp.task('watch', function () {
	livereload.listen();
	gulp.watch('js/*.js', function () {
		livereload();
	});
});


// Watch Task
gulp.task('open-browser', function () {
	var options = {
		url: "http://localhost:5007"
	};
	gulp.src("./index.html")
		.pipe(open("", options));
});


// Default
gulp.task('default', ['start-server', 'watch', 'open-browser']);