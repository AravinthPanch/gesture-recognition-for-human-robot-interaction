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

var joints = {},
	limbs = {},
	jointNames = [
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


define(['jquery', 'three', 'trackBallControl'], function ($, THREE) {

	function initDom() {
		container = document.createElement('div');
		document.body.appendChild(container);

		var title = document.createElement('div');
		title.innerHTML = 'Human Robot Interaction';
		title.className = 'appTitle';
		container.appendChild(title);
	}

	function initScene() {
		app.scene = new THREE.Scene();
	}

	function initCamera() {
		app.camera = new THREE.PerspectiveCamera(70, width / height, 1, 10000);
		//app.camera.position.y = 500;
		//app.camera.position.x = 1000;
		app.camera.position.z = 1000;
		app.controls = new THREE.TrackballControls(app.camera);
	}

	function initRenderer() {
		app.renderer = new THREE.WebGLRenderer();
		app.renderer.setSize(width, height);
		app.renderer.setClearColor(0xffffff);
		container.appendChild(app.renderer.domElement);
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
		plane.position.z = 5000;
		//plane.position.x = -250;
		plane.rotation.x = 3 * (Math.PI / 2);
		app.scene.add(plane);
	}

	var i = 0;

	function renderFromData() {
		if (i < skeletonData.length) {
			$.each(skeletonData[i], function (key, val) {
				if (key !== "FRAME") {
					joints[key].position.x = val[0];
					joints[key].position.y = val[1];
					joints[key].position.z = -val[2];
				}
			});
		}
		i++;
		app.renderer.render(app.scene, app.camera);
	}

	function render() {
		$.each(app.skeletonBuffer, function (key, val) {
			var positionConfidence = parseInt(val[3]);
			if (key !== "FRAME" && positionConfidence >= 0.5) {
				joints[key].position.x = val[0];
				joints[key].position.y = val[1];
				joints[key].position.z = -val[2];
			}
		});
		app.renderer.render(app.scene, app.camera);
	}


	function animate() {
		requestAnimationFrame(animate);
		app.controls.update();
		render();
		//renderFromData();
	}

	function init() {
		initDom();
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
