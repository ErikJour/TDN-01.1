import * as THREE from 'three'

//CANVAS
const canvas = document.querySelector('canvas.webgl');
const scene = new THREE.Scene();
const sizes = {
    width: window.innerWidth,
    height: window.innerHeight
}

//COLORS

const taliesenRed = new THREE.Color(0xC89640);  
const oscillatorOneColor = new THREE.Color(0xff8800); 
const tunnelColor = new THREE.Color(0x008285);

const neutraColorPalette = {
    neutraBeige: "#D9D4C5",
    sageGreen: "#A8B79A",
    warmGray: "#A9A39B",
    terracotta: "#C67650",
    paleSkyBlue: "#9EB8C2",
    oliveBrown: "#5A5A44",
    sunlitSand: "#E5C69F",
    mutedTeal: "#6E8D90",
    charcoalGray: "#4A4A4A"
};

//OBJECTS

const levelTopGeometry = new THREE.SphereGeometry(64, 30, 29, 0, Math.PI * 2, 4.27, 2);

const levelMaterial = new THREE.MeshStandardMaterial({
    
    color: taliesenRed});

const levelTopMesh = new THREE.Mesh(levelTopGeometry, levelMaterial);

const levelBottomGeometry = new THREE.PlaneGeometry( 100, 100 );

const levelBottomMesh = new THREE.Mesh(levelBottomGeometry, levelMaterial);

scene.add(levelTopMesh);

scene.add(levelBottomMesh);

levelBottomMesh.position.set(0, -15, 0);
levelBottomMesh.rotation.x = -Math.PI / 2;

// levelTopMesh.rotation.x = Math.PI;

levelTopMesh.position.set(0, 0, 0);
levelTopMesh.castShadow = true;
levelBottomMesh.receiveShadow = true;

//LIGHT

const light = new THREE.AmbientLight(0xffffff, .5);
light.position.set(0, 10, 0);
scene.add(light);

const spotLight = new THREE.SpotLight(neutraColorPalette.paleSkyBlue, .25);
spotLight.position.set(0, 20, 0);
scene.add(spotLight);

//CAMERA
const camera = new THREE.PerspectiveCamera(75, sizes.width / sizes.height);
camera.position.z = 50;
camera.position.set(0, 0, 0);
scene.add(camera);

//RENDERER
const renderer = new THREE.WebGLRenderer({
    canvas: canvas
})

renderer.setSize(sizes.width, sizes.height);

renderer.render(scene, camera);

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

    renderer.render(scene, camera);
};

animate();