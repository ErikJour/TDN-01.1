import * as THREE from 'three'
import { createSpotlight, ambientLightA, directionalLight } from './light';
import { levelBottomMesh, createSphere, createWall } from './objects';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'
import { greyMaterial, labelMaterial } from './noiseParticles';
import { FontLoader } from 'three/examples/jsm/loaders/FontLoader.js'
import { TextGeometry } from 'three/examples/jsm/geometries/TextGeometry.js';

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
const labelSize = 0.08;

function createLabel (xPos, yPos, zPos, word)
{
const wordGeometry = createLetter(word, font);
wordGeometry.computeBoundingBox();
wordGeometry.center();
console.log(wordGeometry.boundingBox);
const wordMesh = new THREE.Mesh(wordGeometry, labelMaterial);
wordMesh.position.set(xPos, yPos, zPos);
wordMesh.scale.set(labelSize, labelSize, labelSize)
wordMesh.castShadow = true;
wordMesh.receiveShadow = true;
wordMesh.transparent = false;
scene.add(wordMesh);

}

const lfoWordX = 0;
const lfoWordY = 2;
const lfoWordZ = -49;
const lfoWord = createLabel (lfoWordX, lfoWordY, lfoWordZ, 'LFO');

});



//ADD LIGHTS
const spotlightNorth = createSpotlight(0, 10, -50, 500);
scene.add(spotlightNorth);
const spotlightSouth = createSpotlight(0, 10, 50, 500);
scene.add(spotlightSouth);
const spotlightWest = createSpotlight(-50, 10, 0, 500);
scene.add(spotlightWest);
const spotlightEast = createSpotlight(50, 10, 0, 500);
scene.add(spotlightEast);

scene.add(ambientLightA);
scene.add(directionalLight);

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

// Controls
const controls = new OrbitControls(camera, canvas)
controls.enableDamping = true

//NOISE

const noiseCenterX = 0;
const noiseCenterY = 0;
const noiseCenterZ = 0;
const noiseGrainGroup = new THREE.Group();
scene.add(noiseGrainGroup);

const grainGeometry = new THREE.BoxGeometry(0.02, 0.02, 0.02);

function createGrain(geometry) {
    geometry = grainGeometry;
    const mesh = new THREE.Mesh(geometry, greyMaterial);
    const radius = 10; 
    const theta = Math.random() * Math.PI * 25;
    const phi = Math.acos(2 * Math.random() - 1);
    mesh.position.set(
        radius * Math.sin(phi) * Math.cos(theta),
        radius * Math.sin(phi) * Math.sin(theta),
        radius * Math.cos(phi)
    );
    mesh.velocity = new THREE.Vector3(
        (Math.random() - 0.5) * 0.01,
        (Math.random() - 0.5) * 0.01,
        (Math.random() - 0.5) * 0.01
    );
    
    return mesh;
}

function updateGrainObject(count) {
    noiseGrainGroup.clear();
    for (let i = 0; i < count; i++) {
        noiseGrainGroup.add(createGrain());
    }
}

noiseGrainGroup.position.set (noiseCenterX, noiseCenterY, noiseCenterZ)

updateGrainObject(5000);

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

//AXIS Helper
// const axisHelper = new THREE.AxesHelper;
// scene.add(axisHelper);
// axisHelper.position.set(0, -3, 0);

//MOVEMENT BOUNDS
const movementBounds = {
    minimumZ: -48,
    maxZ: 48,
    radius: 48
};

//ANIMATE
const animate = () => {
    requestAnimationFrame(animate);

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

       noiseGrainGroup.children.forEach(noiseGrain => {
        noiseGrain.position.add(noiseGrain.velocity);
    
        const maxRadius = 2; 
        if (noiseGrain.position.length() > maxRadius) {
            noiseGrain.position.normalize().multiplyScalar(maxRadius);
            noiseGrain.velocity.negate(); 
        }
    
        noiseGrain.material.opacity = 10; 
    });

    renderer.render(scene, camera);
};

animate();