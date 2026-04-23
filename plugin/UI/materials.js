import * as THREE from 'three'
import { neutraColorPalette } from './colors.js';

const greyMaterial = new THREE.MeshMatcapMaterial({ 
    color: neutraColorPalette.neutraBeige,                   
    transparent: false, 
    opacity: 1
});

const pinkMaterial = new THREE.MeshMatcapMaterial({ 
    color: neutraColorPalette.neutraPink,                   
    transparent: false, 
    opacity: 0.5
});

const whiteMaterial = new THREE.MeshMatcapMaterial({ 
    color: neutraColorPalette.neutraCream,                   
    transparent: false, 
    opacity: 0.5
});

const labelMaterial = new THREE.MeshStandardMaterial({
    color: neutraColorPalette.terracotta, 
    opacity: 0.0,   
    transparent: false,
    roughness: 0.5,  
    metalness: 0.1  
});

const particleMaterial = new THREE.PointsMaterial({
    size: 0.05,
    color: neutraColorPalette.paleSkyBlue,
    transparent: true,
    depthWrite: false,
    blending: THREE.AdditiveBlending,
    vertexColors: false
});


export { labelMaterial, particleMaterial, pinkMaterial, whiteMaterial };