'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/01/15.
 * Contributors:
 */


var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(45, window.innerWidth/window.innerHeight, 1, 1000 );
scene.add(camera);

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );

document.body.appendChild( renderer.domElement );

//    var geometry = new THREE.BoxGeometry( 1, 1, 1 );
//    var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
//    var cube = new THREE.Mesh( geometry, material );
//    scene.add( cube );
//
camera.position.set(0,50,50);
camera.lookAt( scene.position );

//    camera.position.set(0, 0, 100);
//    camera.lookAt(new THREE.Vector3(0, 0, 0));

var material = new THREE.LineBasicMaterial({
	color: 0x0000ff
});

var geometry = new THREE.Geometry();
geometry.vertices.push(new THREE.Vector2(500, 500));


var line = new THREE.Line(geometry, material);

scene.add(line);

var material = new THREE.LineBasicMaterial({
	color: 0x0000ff
});


renderer.render(scene, camera);

//    var render = function () {
//        requestAnimationFrame( render );
//
//        cube.rotation.x += 0.1;
//        renderer.render(scene, camera);
//    };
//
//    render();
