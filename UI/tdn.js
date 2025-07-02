import * as THREE from 'three'

//CANVAS
const canvas = document.querySelector('canvas.webgl');

const scene = new THREE.Scene();

const sizes = {
    width: window.innerWidth,
    height: window.innerHeight
}

//CAMERA
const camera = new THREE.PerspectiveCamera(75, sizes.width / sizes.height);
camera.position.z = 50;
scene.add(camera);

//RENDERER
const renderer = new THREE.WebGLRenderer({
    canvas: canvas
})

renderer.setSize(sizes.width, sizes.height);

renderer.render(scene, camera);

//ANIMATE
const animate = () => {
    requestAnimationFrame(animate);

    renderer.render(scene, camera);
};

animate();