'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */


var width = window.innerWidth,
	height = window.innerHeight,
	container,
	consoleBox,
	outputBox,
	gestureBox;

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


define(['jquery', 'three', 'underscore', 'trackBallControl', 'font', 'jqueryUi'], function ($, THREE, _) {

	/*
	 *
	 * Creates a div under main body to use it as canvas for the threejs renderer
	 * Components such scene, camera and objects will be added to the renderer
	 *
	 * */
	function initDom() {

		container = document.createElement('div');
		document.body.appendChild(container);

		//Jquery Ui components
		consoleBox = document.createElement('div');
		consoleBox.id = "consoleBox";
		document.body.appendChild(consoleBox);

		outputBox = document.createElement('div');
		outputBox.id = "outputBox";
		document.body.appendChild(outputBox);


		gestureBox = document.createElement('div');
		gestureBox.id = "gestureBox";
		document.body.appendChild(gestureBox);

		// Initiate the console ui
		$(function () {
			$("#consoleBox").dialog({
				dialogClass: "consoleBox",
				title: "Console",
				height: 150,
				width: 650,
				position: {my: "left bottom", at: "left bottom", of: window}
			});
		});

		// Initiate the output ui
		$(function () {
			$("#outputBox").dialog({
				dialogClass: "outputBox",
				title: "Output",
				height: 100,
				width: 200,
				position: {my: "left top", at: "left top", of: window}
			});
		});

		// Initiate the gestureBox ui
		$(function () {
			$("#gestureBox").dialog({
				dialogClass: "gestureBox",
				title: "Gesture",
				height: 150,
				width: 400,
				position: {my: "right bottom", at: "right bottom", of: window}
			});
		});
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
			PredictedClass: 0,
			MaximumLikelihood: 0,
			Gesture: "",
			cameraX: 0,
			cameraY: 0,
			cameraZ: 0,
			RightX: 0,
			RightY: 0,
			RightZ: 0,
			LeftX: 0,
			LeftY: 0,
			LeftZ: 0
		};
		var trackerSelection = datGUI.add(guiParams, 'Tracker',
			{
				'Hand Tracker': 1, 'Skeleton Tracker': 2,
				'Hand Tracker From Data': 3, 'Skeleton Tracker From Data': 4
			}
		);

		var predictionFolder = datGUI.addFolder("Prediction Data");
		predictionFolder.add(guiParams, 'PredictedClass').listen();
		predictionFolder.add(guiParams, 'MaximumLikelihood').listen();
		predictionFolder.add(guiParams, 'Gesture').listen();

		//predictionFolder.open();

		var cameraFolder = datGUI.addFolder("WebGL Camera Data");
		cameraFolder.add(guiParams, 'cameraX').listen();
		cameraFolder.add(guiParams, 'cameraY').listen();
		cameraFolder.add(guiParams, 'cameraZ').listen();

		//cameraFolder.open();

		var handFolder = datGUI.addFolder("Hand Data");
		handFolder.add(guiParams, 'RightX').listen();
		handFolder.add(guiParams, 'RightY').listen();
		handFolder.add(guiParams, 'RightZ').listen();
		handFolder.add(guiParams, 'LeftX').listen();
		handFolder.add(guiParams, 'LeftY').listen();
		handFolder.add(guiParams, 'LeftZ').listen();

		//handFolder.open();

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
		app.camera.position.x = 0;
		app.camera.position.y = 0;
		app.camera.position.z = 3500;

		// Add dom element as second element on which trackball controller should work
		app.controls = new THREE.TrackballControls(app.camera, app.renderer.domElement);
	}

	function startHandTracking() {
		jointNames = handTrackingJoints;
		clearScene();
		drawJoints();
	}

	function startSkeletonTracking() {
		jointNames = skeletonTrackingJoints;
		clearScene();
		drawJoints();
	}

	function clearScene() {
		// Dont remove plane mesh, triangle mesh and sensor mesh
		var objsToRemove = _.rest(app.scene.children, 3);
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

		// Brown colored wireframe
		var sphereMatRIGHT = new THREE.MeshBasicMaterial({
			color: 0x663300, wireframe: true
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


	function drawSensorTriangle() {
		var triangleGeometry = new THREE.Geometry();
		triangleGeometry.vertices.push(new THREE.Vector3(0, -300, 0));
		triangleGeometry.vertices.push(new THREE.Vector3(-300, 150, 0));
		triangleGeometry.vertices.push(new THREE.Vector3(300, 150, 0));
		triangleGeometry.faces.push(new THREE.Face3(0, 1, 2));
		triangleGeometry.computeFaceNormals();

		var triangleMaterial = new THREE.MeshBasicMaterial({
			color: 0x999999,
			wireframe: true
		});
		var triangleMesh = new THREE.Mesh(triangleGeometry, triangleMaterial);

		app.scene.add(triangleMesh);

		var sphereGeo = new THREE.SphereGeometry(20);
		var sphereMatRIGHT = new THREE.MeshBasicMaterial({
			color: 0xff0000, wireframe: true
		});
		var sphereMesh = new THREE.Mesh(sphereGeo, sphereMatRIGHT);

		app.scene.add(sphereMesh);
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

			guiParams.RightX = app.skeletonBuffer.RIGHT[0];
			guiParams.RightY = app.skeletonBuffer.RIGHT[1];
			guiParams.RightZ = app.skeletonBuffer.RIGHT[2];
		}

		if ('LEFT' in app.skeletonBuffer) {
			joints['LEFT'].position.x = app.skeletonBuffer.LEFT[0];
			joints['LEFT'].position.y = app.skeletonBuffer.LEFT[1];
			joints['LEFT'].position.z = app.skeletonBuffer.LEFT[2];

			guiParams.LeftX = app.skeletonBuffer.LEFT[0];
			guiParams.LeftY = app.skeletonBuffer.LEFT[1];
			guiParams.LeftZ = app.skeletonBuffer.LEFT[2];
		}

		if ('OUTPUT' in app.skeletonBuffer) {
			guiParams.PredictedClass = app.skeletonBuffer.OUTPUT[0];
			guiParams.MaximumLikelihood = app.skeletonBuffer.OUTPUT[1];
			$("#outputBox").text(app.skeletonBuffer.OUTPUT[0] + " : " + app.skeletonBuffer.OUTPUT[1].toFixed(2));
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

			if ('GESTURE' in handData[i]) {
				$('#gestureBox').text(handData[i].GESTURE);

				var timer = setTimeout(function () {
					$('#gestureBox').text("")
				}, 5000);
			}

			$('#consoleBox').prepend("<div class='log'>" + JSON.stringify(handData[i]) + "</div>");

			if ('RIGHT' in handData[i]) {
				joints['RIGHT'].position.x = handData[i].RIGHT[0];
				joints['RIGHT'].position.y = handData[i].RIGHT[1];
				joints['RIGHT'].position.z = handData[i].RIGHT[2];

				guiParams.RightX = handData[i].RIGHT[0];
				guiParams.RightY = handData[i].RIGHT[1];
				guiParams.RightZ = handData[i].RIGHT[2];
			}

			if ('LEFT' in handData[i]) {
				joints['LEFT'].position.x = handData[i].LEFT[0];
				joints['LEFT'].position.y = handData[i].LEFT[1];
				joints['LEFT'].position.z = handData[i].LEFT[2];

				guiParams.LeftX = handData[i].LEFT[0];
				guiParams.LeftY = handData[i].LEFT[1];
				guiParams.LeftZ = handData[i].LEFT[2];
			}

			if ('OUTPUT' in handData[i]) {
				guiParams.PredictedClass = handData[i].OUTPUT[0];
				guiParams.MaximumLikelihood = handData[i].OUTPUT[1];
				$("#outputBox").text(handData[i].OUTPUT[0] + " : " + handData[i].OUTPUT[1].toFixed(2));
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

		guiParams.cameraX = app.camera.position.x;
		guiParams.cameraY = app.camera.position.y;
		guiParams.cameraZ = app.camera.position.z;


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
		drawPlane();
		drawSensorTriangle();
		startHandTracking(); // Start Hand Tracker by Default
		animate();
	}

	return {
		init: init
	}

});
