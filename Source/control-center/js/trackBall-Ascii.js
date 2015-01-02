'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */

var container;

var camera, light1, light2, controls, effect, scene, renderer;

var sphere, plane;

var start = Date.now();

init();

animate();

function init() {

	var width = window.innerWidth;
	var height = window.innerHeight;

	container = document.createElement('div');
	document.body.appendChild(container);

	var info = document.createElement('div');
	info.style.position = 'absolute';
	info.style.top = '10px';
	info.style.width = '100%';
	info.style.textAlign = 'center';
	info.innerHTML = 'Drag to change the view';

	container.appendChild(info);

	camera = new THREE.PerspectiveCamera(70, width / height, 1, 1000);
	camera.position.y = 150;
	camera.position.z = 500;

	controls = new THREE.TrackballControls(camera);

	scene = new THREE.Scene();

	light1 = new THREE.PointLight(0xffffff);
	light1.position.set(500, 500, 500);
	scene.add(light1);

	light2 = new THREE.PointLight(0xffffff, 0.25);
	light2.position.set(-500, -500, -500);
	scene.add(light2);

	var sphereGeo = new THREE.SphereGeometry(200, 20, 10);
	var sphereMat = new THREE.MeshLambertMaterial({
		shading: THREE.FlatShading,
		color: 0xff0000
	});
	sphere = new THREE.Mesh(sphereGeo, sphereMat);
	scene.add(sphere);

	var planeGeo = new THREE.PlaneGeometry(400, 400);
	var planeMat = new THREE.MeshBasicMaterial({
		color: 0xc0c0c0
	});
	plane = new THREE.Mesh(planeGeo, planeMat);
	plane.position.y = -200;
	plane.rotation.x = -Math.PI / 2;
	scene.add(plane);

	renderer = new THREE.WebGLRenderer();
	renderer.setSize(width, height);
	renderer.setClearColor(0xffffff);
	container.appendChild(renderer.domElement);
	//renderer.render(scene, camera);

	//effect = new THREE.AsciiEffect(renderer);
	//effect.setSize(width, height);
	//container.appendChild(effect.domElement);

	window.addEventListener('resize', onWindowResize, false);


	function onWindowResize() {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize(window.innerWidth, window.innerHeight);
		//effect.setSize(window.innerWidth, window.innerHeight);
		//effect.render(scene, camera);
	}

}

function animate() {
	requestAnimationFrame(animate);
	controls.update();
	renderer.render(scene, camera);
}
