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
var limbs = {};
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

	//var but = document.createElement('button');
	//but.type = 'button';
	//but.innerHTML = 'Rotate';
	//but.style.position = 'absolute';
	//but.style.top = '10px';
	//but.style.margin = '10px';
	//but.onclick = butClick;
	//container.appendChild(but);

	scene = new THREE.Scene();

	camera = new THREE.PerspectiveCamera(70, width / height, 1, 10000);
	camera.position.y = 500;
	camera.position.x = 1000;
	camera.position.z =	1000;

	controls = new THREE.TrackballControls(camera);

	var sphereGeo = new THREE.SphereGeometry(20);
	var sphereMat = new THREE.MeshBasicMaterial({
		color: 0xff0000, wireframe: true
	});

	$.each(jointNames, function (key, val) {
		joints[val] = new THREE.Mesh(sphereGeo, sphereMat);
		scene.add(joints[val]);
	});


	//var lineMat = new THREE.LineBasicMaterial({
	//	color: 0x0000ff
	//});
	//var lineGeo = new THREE.Geometry();
	//lineGeo.vertices.push(
	//	new THREE.Vector3(skeletonData[0]["HEAD"][0], skeletonData[0]["HEAD"][1], -skeletonData[0]["NECK"][2]),
	//	new THREE.Vector3(skeletonData[0]["NECK"][0], skeletonData[0]["NECK"][1], -skeletonData[0]["NECK"][2])
	//);
	//var line = new THREE.Line(lineGeo, lineMat);
	//scene.add(line);


	var planeGeo = new THREE.PlaneGeometry(5000, 5000);
	var planeMat = new THREE.MeshBasicMaterial({
		color: 0xc0c0c0

	});
	plane = new THREE.Mesh(planeGeo, planeMat);
	plane.position.y = 500;
	plane.position.z = 2000;
	plane.position.x = -500;
	plane.rotation.x = 3 * (Math.PI / 2);
	scene.add(plane);

	$.each(skeletonData[0], function (key, val) {
		if (key !== "FRAME") {
			joints[key].position.x = val[0];
			joints[key].position.y = val[1];
			joints[key].position.z = -val[2];
		}

		if (key === "TORSO") {
			plane.position.z = -val[2];
			plane.rotation.x = 3 * (Math.PI / 2);
		}

		if (key === "LEFT_FOOT") {
			plane.position.y = val[1] - 500;
		}
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
	//renderer.render(scene, camera);

}

var i = 0;
function render() {

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


	renderer.render(scene, camera);
}

function butClick() {
	$.each(joints, function (key, val) {
		val.rotation.x += 10
	});

	renderer.render(scene, camera);
}