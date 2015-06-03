'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */


var width = window.innerWidth,
	height = window.innerHeight,
	container;

var renderStatus = 1;

var joints = {},
	jointNames = [],
	handTrackingJoints = ["RIGHT", "LEFT"],
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

var datGUI = {},
	guiParams = {},
	datGuiSize = {
		width: 400
	};


define(['jquery', 'three', 'underscore', 'trackBallControl', 'font'], function ($, THREE, _) {

	/*
	 *
	 * Creates a div under main body to use it as canvas for the threejs renderer
	 * Components such scene, camera and objects will be added to the renderer
	 *
	 * */
	function initDom() {
		container = document.createElement('div');
		document.body.appendChild(container);
	}


	/*
	 *
	 * Creates a dat.GUI
	 * Adds the parameters and eventHandlers to GUI
	 *
	 * */
	function initGui() {

		datGUI = new dat.GUI({
			width: datGuiSize.width
		});

		// Add GUI parameters
		guiParams = {
			Tracker: 'Hand Tracker',
			'Predicted Class': 0,
			'Maximum Likelihood': 0,
			Gesture: ""
		};
		var trackerSelection = datGUI.add(guiParams, 'Tracker',
			{
				'Hand Tracker': 1, 'Skeleton Tracker': 2,
				'Hand Tracker From Data': 3, 'Skeleton Tracker From Data': 4
			}
		);
		datGUI.add(guiParams, 'Predicted Class');
		datGUI.add(guiParams, 'Maximum Likelihood');
		datGUI.add(guiParams, 'Gesture');


		// Based on the tracker selected, draw the joints after clearing the scene
		trackerSelection.onChange(function (value) {
			renderStatus = parseInt(value);
			switch (renderStatus) {
				case 1:
					startHandTracking();
					break;
				case 2:
					startSkeletonTracking();
					break;
				case 3:
					startHandTracking();
					break;
				case 4:
					startSkeletonTracking();
					break;
			}
		});
	}


	/*
	 *
	 * Creates a threejs scene
	 *
	 * */
	function initScene() {
		app.scene = new THREE.Scene();
	}


	/*
	 *
	 * Creates WebGL renderer and appends to the DOM
	 *
	 * */
	function initRenderer() {
		app.renderer = new THREE.WebGLRenderer();
		app.renderer.setSize(width, height);
		app.renderer.setClearColor(0xffffff);
		container.appendChild(app.renderer.domElement);
	}


	/*
	 *
	 * Creates a camera for the initial view
	 * TrackballControll changes the camera view based mouse events
	 *
	 * TODO: Camera is must be mirrored so that when skeleton comes closer to camera, objects should get bigger
	 *
	 * */
	function initCamera() {
		app.camera = new THREE.PerspectiveCamera(70, width / height, 1, 10000);
		//app.camera.position.y = 500;
		//app.camera.position.x = 1000;
		app.camera.position.z = 2000;

		// Add dom element as second element on which trackball controller should work
		app.controls = new THREE.TrackballControls(app.camera, app.renderer.domElement);
	}

	function startHandTracking() {
		jointNames = handTrackingJoints;
		clearScene();
		drawJoints();
		drawPlane();
	}

	function startSkeletonTracking() {
		jointNames = skeletonTrackingJoints;
		clearScene();
		drawJoints();
		drawPlane();
	}

	function clearScene() {
		var objsToRemove = _.rest(app.scene.children, 1);
		_.each(objsToRemove, function (object) {
			app.scene.remove(object);
		});
	}


	/*
	 * Draw only hand joints in red and blue (right and left).
	 * If not draw all the joints of the skeleton
	 * */
	function drawJoints() {
		var sphereGeo = new THREE.SphereGeometry(20);

		// Red colored wireframe
		var sphereMatRIGHT = new THREE.MeshBasicMaterial({
			color: 0xff0000, wireframe: true
		});

		// Blue colored wireframe
		var sphereMatLEFT = new THREE.MeshBasicMaterial({
			color: 0x0000ff, wireframe: true
		});

		$.each(jointNames, function (key, val) {

			if (val == "RIGHT") {
				joints[val] = new THREE.Mesh(sphereGeo, sphereMatRIGHT);
			}
			else if (val == "LEFT") {
				joints[val] = new THREE.Mesh(sphereGeo, sphereMatLEFT);
			}
			else {
				// If skeleton, Draw all the joints in red
				joints[val] = new THREE.Mesh(sphereGeo, sphereMatRIGHT);
			}

			app.scene.add(joints[val]);
		});
	}


	/*
	 * Draw plane below the skeleton as base. Position of this plane
	 * is calculated by calculating the height of the skeleton
	 * */
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


	function drawTitle() {
		var material = new THREE.MeshPhongMaterial({
			color: 0xdddddd
		});
		var textGeom = new THREE.TextGeometry('Human Robot Interaction', {
			font: "helvetiker",
			weight: 'normal'
		});
		var textMesh = new THREE.Mesh(textGeom, material);

		app.scene.add(textMesh);

		// Do some optional calculations. This is only if you need to get the
		// width of the generated text
		textGeom.computeBoundingBox();
		textGeom.textWidth = textGeom.boundingBox.max.x - textGeom.boundingBox.min.x;

	}

	function renderHand() {
		if ('RIGHT' in app.skeletonBuffer) {
			joints['RIGHT'].position.x = app.skeletonBuffer.RIGHT[0];
			joints['RIGHT'].position.y = app.skeletonBuffer.RIGHT[1];
			joints['RIGHT'].position.z = app.skeletonBuffer.RIGHT[2];
		}

		if ('LEFT' in app.skeletonBuffer) {
			joints['LEFT'].position.x = app.skeletonBuffer.LEFT[0];
			joints['LEFT'].position.y = app.skeletonBuffer.LEFT[1];
			joints['LEFT'].position.z = app.skeletonBuffer.LEFT[2];
		}

		if ('OUTPUT' in app.skeletonBuffer) {
			guiParams['Predicted Class'] = app.skeletonBuffer.OUTPUT[0];
			guiParams['Maximum Likelihood'] = app.skeletonBuffer.OUTPUT[0];
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


	function animate() {
		//setTimeout(function () {
		//	requestAnimationFrame(animate);
		//
		//}, 1000 / 30);

		requestAnimationFrame(animate);
		app.controls.update();

		switch (renderStatus) {
			case 1:
				renderHand();
				break;
			case 2:
				renderSkeleton();
				break;
			case 3:
				renderHandFromData();
				break;
			case 4:
				renderSkeletonFromData();
				break;
		}

	}

	function init() {
		initDom();
		initGui();
		initScene();
		initRenderer();
		initCamera();
		//drawTitle();
		startHandTracking(); // Start Hand Tracker by Default
		animate();
	}

	return {
		init: init
	}

});
