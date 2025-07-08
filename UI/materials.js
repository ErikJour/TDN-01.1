import * as THREE from 'three'
import { neutraColorPalette } from './colors.js';

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

const particleMaterial = new THREE.PointsMaterial();
particleMaterial.size = 0.1;
particleMaterial.sizeAttenuation = true;
particleMaterial.color.set('white');


export { greyMaterial, labelMaterial, particleMaterial };