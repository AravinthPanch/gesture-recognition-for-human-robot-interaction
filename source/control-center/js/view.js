'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */


var width = window.innerWidth,
	height = window.innerHeight,
	container = {};

var renderStatus = 'renderHand';

var joints = {},
	limbs = {},
	jointNames = [],
	handTrackingJoints = ["HAND"],
	skeletonTrackingJoints = [
		"HEAD",
		"NECK",
		"LEFT_SHOULDER",
		"RIGHT_SHOULDER",
		"LEFT_ELBOW",
		"RIGHT_ELBOW",
		"LEFT_HAND",
		"RIGHT_HAND",
		"TORSO",
		"LEFT_HIP",
		"RIGHT_HIP",
		"LEFT_KNEE",
		"RIGHT_KNEE",
		"LEFT_FOOT",
		"RIGHT_FOOT"
	];


define(['jquery', 'three', 'socketio', 'underscore', 'semantic', 'trackBallControl'], function ($, THREE, socketio, _) {

	var socket = socketio.connect();

	function startHandTracking() {
		//socket.emit('init', 'handTracking');
		renderStatus = 'renderHand';
		jointNames = handTrackingJoints;
		clearScene();
		drawJoints();
		$('.renderStatusLabel').text(renderStatus);
	}

	function startSkeletonTracking() {
		//socket.emit('init', 'skeletonTracking');
		renderStatus = 'renderSkeleton';
		jointNames = skeletonTrackingJoints;
		clearScene();
		drawJoints();
		$('.renderStatusLabel').text(renderStatus);
	}

	function startRenderFromData() {
		renderStatus += "FromData";
		$('.renderStatusLabel').text(renderStatus);
	}

	function initControlPanel() {
		var title = document.createElement('div');
		title.innerHTML = 'Human Robot Interaction';
		title.className = 'appTitle';

		var hButton = document.createElement('button');
		hButton.innerHTML = "Hand Tracking";
		hButton.className = 'ui primary button';
		hButton.style.cssText = "margin: 10px;";
		hButton.addEventListener("click", startHandTracking);

		var sButton = document.createElement('button');
		sButton.innerHTML = "Skeleton Tracking";
		sButton.className = 'ui primary button';
		sButton.style.cssText = "margin: 10px;";
		sButton.addEventListener("click", startSkeletonTracking);

		var fromDataButton = document.createElement('button');
		fromDataButton.innerHTML = "Render from Data";
		fromDataButton.className = 'ui primary button';
		fromDataButton.style.cssText = "margin: 10px;";
		fromDataButton.addEventListener("click", startRenderFromData);

		var statusLabel = document.createElement('div');
		statusLabel.innerHTML = renderStatus;
		statusLabel.className = 'ui label big renderStatusLabel';
		statusLabel.style.cssText = "margin: 10px;";

		var predictionLabel = document.createElement('div');
		predictionLabel.innerHTML = "Predicted Class : , Maximum Likelihood : ";
		predictionLabel.className = 'ui label big predictionLabel';
		predictionLabel.style.cssText = "margin: 10px;";

		container.appendChild(title);
		container.appendChild(hButton);
		container.appendChild(sButton);
		container.appendChild(fromDataButton);
		container.appendChild(statusLabel);
		container.appendChild(predictionLabel);
	}

	function initDom() {
		container = document.createElement('div');
		document.body.appendChild(container);
	}

	function initScene() {
		app.scene = new THREE.Scene();
	}

	function initRenderer() {
		app.renderer = new THREE.WebGLRenderer();
		app.renderer.setSize(width, height);
		app.renderer.setClearColor(0xffffff);
		container.appendChild(app.renderer.domElement);
	}

	function initCamera() {
		app.camera = new THREE.PerspectiveCamera(70, width / height, 1, 10000);
		//app.camera.position.y = 500;
		//app.camera.position.x = 1000;
		app.camera.position.z = 2000;
		app.controls = new THREE.TrackballControls(app.camera);
	}

	function clearScene() {
		var objsToRemove = _.rest(app.scene.children, 1);
		_.each(objsToRemove, function (object) {
			app.scene.remove(object);
		});
	}

	function drawJoints() {
		var sphereGeo = new THREE.SphereGeometry(20);
		var sphereMat = new THREE.MeshBasicMaterial({
			color: 0xff0000, wireframe: true
		});

		$.each(jointNames, function (key, val) {
			joints[val] = new THREE.Mesh(sphereGeo, sphereMat);
			app.scene.add(joints[val]);
		});
	}

	function drawPlane() {
		var planeGeo = new THREE.PlaneGeometry(5000, 5000);
		var planeMat = new THREE.MeshBasicMaterial({
			color: 0xc0c0c0
		});
		var plane = new THREE.Mesh(planeGeo, planeMat);
		plane.position.y = -1500;
		plane.position.z = 200;
		//plane.position.x = -250;
		plane.rotation.x = 3 * (Math.PI / 2);
		app.scene.add(plane);
	}

	var i = 0;

	function renderSkeletonFromData() {
		if (i < skeletonData.length) {
			$.each(skeletonData[i], function (key, val) {

				if (key !== "FRAME") {
					var positionConfidence = parseFloat(val[3]);
					console.log(positionConfidence)
					if (positionConfidence >= 0.5) {
						joints[key].position.x = val[0];
						joints[key].position.y = val[1];
						joints[key].position.z = val[2];
					}
				}
			});
		}
		i++;
		app.renderer.render(app.scene, app.camera);
	}

	function renderHandFromData() {
		if (i < handData.length) {
			if ('HAND' in handData[i]) {
				joints['HAND'].position.x = handData[i].HAND[1];
				joints['HAND'].position.y = handData[i].HAND[2];
				joints['HAND'].position.z = handData[i].HAND[3];
			}
		}
		i++;
		app.renderer.render(app.scene, app.camera);
	}


	function renderHand() {
		if ('HAND' in app.skeletonBuffer) {
			joints['HAND'].position.x = app.skeletonBuffer.HAND[1];
			joints['HAND'].position.y = app.skeletonBuffer.HAND[2];
			joints['HAND'].position.z = app.skeletonBuffer.HAND[3];
		}

		if ('OUTPUT' in app.skeletonBuffer) {
			var predictionLabel = "Predicted Class : " + app.skeletonBuffer.OUTPUT[0]
				+ " , Maximum Likelihood : " + app.skeletonBuffer.OUTPUT[1];

			$('.predictionLabel').text(predictionLabel);
		}

		app.renderer.render(app.scene, app.camera);
	}


	function renderSkeleton() {
		$.each(app.skeletonBuffer, function (key, val) {
			var positionConfidence = parseInt(val[3]);
			if (key !== "FRAME") {
				joints[key].position.x = val[0];
				joints[key].position.y = val[1];
				joints[key].position.z = -val[2];
			}
		});
		app.renderer.render(app.scene, app.camera);
	}


	function animate() {
		//setTimeout(function () {
		//	requestAnimationFrame(animate);
		//
		//}, 1000 / 30);

		requestAnimationFrame(animate);
		app.controls.update();

		switch (renderStatus) {
			case 'renderHandFromData':
				renderHandFromData();
				break;
			case 'renderSkeletonFromData':
				renderSkeletonFromData();
				break;
			case 'renderHand':
				renderHand();
				break;
			case 'renderSkeleton':
				renderSkeleton();
				break;
		}

	}

	function init() {
		initDom();
		initControlPanel();
		initScene();
		initCamera();
		drawPlane();
		drawJoints();
		initRenderer();
		animate();
	}

	return {
		init: init
	}

});
