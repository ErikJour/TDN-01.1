import * as THREE from 'three'
import { neutraColorPalette } from './colors.js';
import { particleMaterial } from './materials.js'
import { scene } from './main.js';

const parameters = {};

parameters.count = 1000;
parameters.size = 0.02;

const generatorGalaxy = () => 
{
    const geometry = new THREE.BufferGeometry();

    const positions = new Float32Array(parameters.count * 3);

    for (let i = 0; i < parameters.count; i++) {
        const i3 = i * 3;
        positions[i3 + 0] = Math.random() - 0.5;
        positions[i3 + 1] = Math.random() - 0.5;
        positions[i3 + 2] = Math.random() - 0.5;

    }

    geometry.setAttribute(
        'position',
        new THREE.BufferAttribute(positions, 3)
    )

    const material = new THREE.PointsMaterial({
        size: parameters.size,
        sizeAttenuation: true,
        depthWrite: false,
        blending: THREE.AdditiveBlending
    })

    const points = new THREE.Points(geometry, material);

    scene.add(points);

}

generatorGalaxy();

export { generatorGalaxy };