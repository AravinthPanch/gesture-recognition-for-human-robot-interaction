'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */





var container;

var camera, light1, light2, controls, scene, renderer;

var sphere, plane;

var joints = {};
var jointNames = [
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


init();

animate();

function init() {

	var width = window.innerWidth;
	var height = window.innerHeight;

	container = document.createElement('div');
	document.body.appendChild(container);

	scene = new THREE.Scene();

	camera = new THREE.PerspectiveCamera(70, width / height, 1, 10000);
	camera.position.z = 5000;

	controls = new THREE.TrackballControls(camera);

	var sphereGeo = new THREE.SphereGeometry(20);
	var sphereMat = new THREE.MeshBasicMaterial({
		color: 0xff0000, wireframe: true
	});

	$.each(jointNames, function (key, val) {
		joints[val] = new THREE.Mesh(sphereGeo, sphereMat);
		scene.add(joints[val]);
	});

	renderer = new THREE.WebGLRenderer();
	renderer.setSize(width, height);
	renderer.setClearColor(0xffffff);
	container.appendChild(renderer.domElement);
}

function animate() {
	requestAnimationFrame(animate);
	controls.update();
	render();

}

var i = 0;
function render() {

	if (i < skeletonData.length) {
		$.each(skeletonData[i], function (key, val) {
			if (key !== "FRAME") {
				joints[key].position.x = val[0];
				joints[key].position.y = val[1];
				joints[key].position.z = val[2];
			}
		});
	}

	i++;

	renderer.render(scene, camera);
}