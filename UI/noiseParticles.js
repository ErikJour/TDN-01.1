import * as THREE from 'three'
import { neutraColorPalette } from './colors.js';
import { particleMaterial } from './materials.js'

//GEOMETRY
const particleGeometry = new THREE.BufferGeometry();
const count = 250000;
const positions = new Float32Array(count * 3);

const amt = 50;

for (let i = 0; i < count * 3; i++) 
{
    positions[i] = (Math.random() - 0.5) * amt;
}

particleGeometry.setAttribute(
    'position',
    new THREE.BufferAttribute(positions, 3)
)

const particles = new THREE.Points(particleGeometry, particleMaterial);

export { particles, count, positions };
