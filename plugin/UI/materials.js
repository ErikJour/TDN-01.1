import * as THREE from 'three'
import { neutraColorPalette } from './colors.js';


const particleMaterial = new THREE.PointsMaterial({
    size: 0.05,
    color: neutraColorPalette.paleSkyBlue,
    transparent: true,
    depthWrite: false,
    blending: THREE.AdditiveBlending,
    vertexColors: false
});


export { particleMaterial };