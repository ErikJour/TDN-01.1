import * as THREE from 'three'
import * as JUCE from './javascript'
import { ambientLightA, initializeLights } from './light.ts';
import { initializeObjects } from './objects';
import { NOISE_ELEMENTS } from "./noise/noiseParticlesNew";
import { initializeJuceRelays } from "./juceRelays";
import { initializeFilter } from "./filter";

//=======================================================
//Variables
//=======================================================
let juceRelays = null;


//=======================================================
//Canvas
//=======================================================
const canvas = document.querySelector('canvas.webgl');
export const scene = new THREE.Scene();
const sizes = {
    width: window.innerWidth,
    height: window.innerHeight
}

//=======================================================
//Camera
//=======================================================
export const camera = new THREE.PerspectiveCamera(75, sizes.width / sizes.height);
camera.position.z = 50;
camera.position.set(0, 0, 50);
scene.add(camera);

//RENDERER
const renderer = new THREE.WebGLRenderer({
    canvas: canvas
})

renderer.setSize(sizes.width, sizes.height);
renderer.render(scene, camera);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2))
renderer.shadowMap.enabled = true
renderer.shadowMap.type = THREE.PCFSoftShadowMap

//=======================================================
//Initialize Objects
//=======================================================
initializeObjects(scene);
scene.add(NOISE_ELEMENTS.NOISE_POINTS);
juceRelays = initializeJuceRelays(JUCE);
initializeFilter(scene, camera);
initializeLights(scene);

//=======================================================
//Event Listener
//=======================================================
window.__JUCE__.backend.addEventListener("EnvelopeValue", (event) => {
    ambientLightA.intensity  = event * 20;

});

const clock = new THREE.Clock();

//=======================================================
//Animation Loop
//=======================================================
const animate = () => {
    requestAnimationFrame(animate);


    const elapsedTime = clock.getElapsedTime();

    //UPDATE PARTICLES
    // points.rotation.y = elapsedTime / 100;

    renderer.render(scene, camera);
};

animate();

