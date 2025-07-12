import * as THREE from 'three'
import * as JUCE from './javascript/index.js'
import { createSpotlight, ambientLightA } from './light';
import { levelBottomMesh, createSphere, createWall } from './objects';
import { pinkMaterial, labelMaterial, whiteMaterial } from './materials.js';
import { FontLoader } from 'three/examples/jsm/loaders/FontLoader.js'
import { TextGeometry } from 'three/examples/jsm/geometries/TextGeometry.js';
import { particles, count } from './noiseParticles.js';
import { neutraColorPalette } from './colors.js';
import { arrowUp, arrowDown, arrowLeft, arrowRight, arrowGroup } from './arrows.js'

//TEXTURES
const textureLoader = new THREE.TextureLoader();
const stainedGlassTextureC = textureLoader.load('textures/stainedGlassWaveB.jpg');

//CANVAS
const canvas = document.querySelector('canvas.webgl');
const scene = new THREE.Scene();
const sizes = {
    width: window.innerWidth,
    height: window.innerHeight
}

//ADD OBJECTS
const northSphere = createSphere (4, 30, 29);
northSphere.position.set(0, 22, -50);
scene.add(northSphere);
northSphere.material.map = stainedGlassTextureC;

const southSphere = createSphere (4, 30, 29);
southSphere.position.set(0, 22, 50);
scene.add(southSphere);

const westSphere = createSphere (4, 30, 29);
westSphere.position.set(-50, 22, 0);
scene.add(westSphere);

const eastSphere = createSphere (4, 30, 29);
eastSphere.position.set(50, 22, 0);
scene.add(eastSphere);

scene.add(levelBottomMesh);
const backWall = createWall(100, 100);
scene.add(backWall);
const leftWall = createWall(100, 100);
scene.add(leftWall);
const rightWall = createWall(100, 100);
scene.add(rightWall);
const frontWall = createWall(100, 100);
scene.add(frontWall);
const ceiling = createWall(100, 100);
scene.add(ceiling);
levelBottomMesh.position.set(0, -10, 0);
levelBottomMesh.rotation.x = -Math.PI / 2;
ceiling.position.set(0, 20, 0);
ceiling.rotation.x = Math.PI / 2;
backWall.position.set(0, 0, -50);
leftWall.rotateY(Math.PI * .5);
leftWall.position.set(-50, 0, 0);
rightWall.rotateY(Math.PI * 1.5);
rightWall.position.set(50, 0, 0);
frontWall.rotateY(Math.PI);
frontWall.position.set(0, 0, 50);

// //NEW NOISE PARTICLES
scene.add(particles);
particles.material.transparent = true;
particles.material.alphaTest = 0.1; 
particles.material.depthWrite = false; 
particles.material.blending = THREE.AdditiveBlending; 
particles.material.color.set(neutraColorPalette.neutraPink)

//NOISE TYPE SELECTION
const noiseType = JUCE.getToggleState("noiseType");

//WHITE
// noiseType.setValue(false);
// particles.material.color.set(neutraColorPalette.neutraCream)

//PINK
noiseType.setValue(true);
particles.material.color.set(neutraColorPalette.neutraPink)

//ARROWS
scene.add(arrowUp);
scene.add(arrowDown);
scene.add(arrowLeft);
scene.add(arrowRight);
scene.add(arrowGroup);
arrowGroup.position.set(0, 5, -49);

//ADD LABELS
const fontLoader = new FontLoader();
fontLoader.load("fonts/P22 FLLW Exhibition_Regular.json", function(font) {

    function createLetter(letter, font){
    return new TextGeometry(letter, {
         font: font,
        size: 11,
        height: 2,
        curveSegments: 12,
        bevelEnabled: true,
        bevelThickness: .1,
        bevelSize: 0.5,
        bevelOffset: 0,
        bevelSegments: 5
    });

}
const labelSize = 0.15;

function createLabel (xPos, zPos, word)
{
const wordGeometry = createLetter(word, font);
wordGeometry.computeBoundingBox();
wordGeometry.center();
console.log(wordGeometry.boundingBox);
const wordMesh = new THREE.Mesh(wordGeometry, labelMaterial);
const yPos = 10;
wordMesh.position.set(xPos, yPos, zPos);
wordMesh.scale.set(labelSize, labelSize, 0)
wordMesh.castShadow = true;
wordMesh.receiveShadow = true;
wordMesh.transparent = false;
scene.add(wordMesh);
return wordMesh;
}

//LFO LABEL
const lfoWordX = 0;
const lfoWordZ = -49;
const lfoWord = createLabel (lfoWordX, lfoWordZ, 'LFO');

//NOISE TYPE LABEL
const noiseTypeX = 0;
const noiseTypeZ = 49;
const noiseTypeWord = createLabel (noiseTypeX, noiseTypeZ, 'Noise Type');
noiseTypeWord.rotation.y = Math.PI;

//ADSR LABEL
const adsrX = -49;
const adsrZ = 0;
const adsrWord = createLabel (adsrX, adsrZ, 'ADSR');
adsrWord.rotation.y = Math.PI / 2;

//FILTERS
const filterX = 49;
const filterZ = 0;
const filterWord = createLabel (filterX, filterZ, 'Filters');
filterWord.rotation.y = Math.PI * 1.5;

});

// ADD LIGHTS
const spotlightNorth = createSpotlight(0, 10, -50, 1000);
scene.add(spotlightNorth);
const spotlightSouth = createSpotlight(0, 10, 50, 1000);
scene.add(spotlightSouth);
const spotlightWest = createSpotlight(-50, 10, 0, 1000);
scene.add(spotlightWest);
const spotlightEast = createSpotlight(50, 10, 0, 1000);
scene.add(spotlightEast);
scene.add(ambientLightA);
ambientLightA.intensity = 8;

//CONTROLS

//CAMERA
const camera = new THREE.PerspectiveCamera(75, sizes.width / sizes.height);
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

//MOVEMENT
let moveForward = false;
let moveBackward = false;
let rotateLeft = false;
let rotateRight = false;
const moveSpeed = 0.4; 
const rotationSpeed = 0.04; 

window.addEventListener('keydown', (event) => {
    event.preventDefault();
    switch (event.key) {
        case 'ArrowUp':
            moveForward = true;
            break;
        case 'ArrowDown':
            moveBackward = true;
            break;
        case 'ArrowLeft':
            rotateLeft = true;
            break;
        case 'ArrowRight':
            rotateRight = true;
            break;
    }
});

window.addEventListener('keyup', (event) => {
    switch (event.key) {
        case 'ArrowUp':
            moveForward = false;
            break;
        case 'ArrowDown':
            moveBackward = false;
            break;
        case 'ArrowLeft':
            rotateLeft = false;
            break;
        case 'ArrowRight':
            rotateRight = false;
            break;
    }
});

//MOVEMENT BOUNDS
const movementBounds = {
    minimumZ: -48,
    maxZ: 48,
    radius: 48
};

const clock = new THREE.Clock();

//ANIMATE
const animate = () => {
    requestAnimationFrame(animate);


    const elapsedTime = clock.getElapsedTime();

    if (rotateLeft) camera.rotation.y += rotationSpeed;
    if (rotateRight) camera.rotation.y -= rotationSpeed;

    const wasdDirection = new THREE.Vector3();
    camera.getWorldDirection(wasdDirection);

    if (moveForward) {
        camera.position.add(wasdDirection.multiplyScalar(moveSpeed));
    }
    if (moveBackward) {
        camera.position.add(wasdDirection.multiplyScalar(-moveSpeed));
    }

    camera.position.z = THREE.MathUtils.clamp(camera.position.z, movementBounds.minimumZ, movementBounds.maxZ);
    const distanceFromCenter = Math.sqrt(camera.position.x ** 2 + camera.position.y ** 2);
    if (distanceFromCenter > movementBounds.radius) {
        const scale = movementBounds.radius / distanceFromCenter;
        camera.position.x *= scale;
        camera.position.y *= scale;
    }

    //UPDATE PARTICLES
    particles.rotation.y = elapsedTime / 100;

    //Wave Animation
    // for (let i = 0; i < count; i++) 
    // {
    //     const i3 = i * 3;
    //     const x = particles.geometry.attributes.position.array[i3];

    //     particles.geometry.attributes.position.array[i3 + 1] = Math.sin(elapsedTime + x);
    // }

    //     particles.geometry.attributes.position.needsUpdate = true;

    renderer.render(scene, camera);
};

animate();