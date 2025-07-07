import * as THREE from 'three'
import { neutraColorPalette } from './colors';


//NOISE==============================================================================================================================================
//Main Noise Particles
const noiseCenterX = 0;
const noiseCenterY = 0;
const noiseCenterZ = -25;
const noiseGrainGroup = new THREE.Group();
// scene.add(noiseGrainGroup);

const greyMaterial = new THREE.MeshStandardMaterial({ 
    color: neutraColorPalette.neutraBeige,              
    emissiveIntensity: 0.2,       
    transparent: false, 
    opacity: 1
});

const labelMaterial = new THREE.MeshStandardMaterial({
    color: neutraColorPalette.terracotta, 
    opacity: 0.0,   
    transparent: false,
    roughness: 0.5,  
    metalness: 0.1  
});

const grainGeometry = new THREE.BoxGeometry(0.02, 0.02, 0.02);

function createGrain(geometry) {
    geometry = grainGeometry;
    const mesh = new THREE.Mesh(geometry, greyMaterial);
    const radius = 4; 
    const theta = Math.random() * Math.PI * 5;
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
// noiseGrainGroup.scale.set(.25, ., .1);



updateGrainObject(500);

export { greyMaterial, labelMaterial };