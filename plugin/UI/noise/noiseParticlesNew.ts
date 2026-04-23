import * as THREE from 'three'
import { neutraColorPalette } from '../colors.js';
import vertexShader from './noiseVertexShader.glsl?raw';
import fragmentShader from './noiseFragmentShader.glsl?raw';

//===========================================================
//Variables
//===========================================================
const noiseClusterRadius: number = 7.0;

//===========================================================
//Uniforms
//===========================================================
const noiseUniforms = {
    uTime:       { value: 0.0 },
    uDensity:    { value: 1.0 },
    uGain:       { value: 0.5 },
    uEnvelope:   { value: 0.0 },
    uPointSize:  { value: 0.1 },
    uColor:      { value: new THREE.Color(neutraColorPalette.neutraCream) },
    uColorGrey:  { value: new THREE.Color(neutraColorPalette.warmGray) },
    uPixelRatio: { value: Math.min(window.devicePixelRatio, 2) },

    uLightPos1:   { value: new THREE.Vector3(0, 0, -25) },
    uLightColor1: { value: new THREE.Color(neutraColorPalette.terracotta) },
    uLightPos2:   { value: new THREE.Vector3(0, 0, -25) },
    uLightColor2: { value: new THREE.Color(neutraColorPalette.terracotta) }
};
//===========================================================
//Geometry
//===========================================================
const noiseParams = {
    maxCount: 150000,
    count: 0,
    size: 0.05
};

const noisePointPositions = new Float32Array(noiseParams.maxCount * 3);
const basePositions = new Float32Array(noiseParams.maxCount * 3);

const noiseGeometry = new THREE.BufferGeometry();
noiseGeometry.setAttribute('position', new THREE.BufferAttribute(noisePointPositions, 3));
noiseGeometry.setAttribute('aBasePosition', new THREE.BufferAttribute(basePositions, 3));

//===========================================================
//Material
//===========================================================
const noiseMaterial = new THREE.ShaderMaterial({
    uniforms: noiseUniforms,
    vertexShader,
    fragmentShader,
    transparent: true,
    depthWrite: false,
    depthTest: true,
    blending: THREE.AdditiveBlending,
});
//===========================================================
//Meshes
//===========================================================
const noisePoints = new THREE.Points(noiseGeometry, noiseMaterial);
noisePoints.scale.x = 0.75;  // squeeze to half width
noisePoints.position.set(0, 4, noiseClusterRadius);
//===========================================================
//Particle Generation
//===========================================================
const noiseCache = new Map();

export function generateNoiseParticles(newCount: number) {
    if (noiseCache.has(newCount)) {
        const cached = noiseCache.get(newCount);
        basePositions.set(cached);
        noisePointPositions.set(cached);
        noiseGeometry.attributes.aBasePosition.needsUpdate = true;
        noiseGeometry.attributes.position.needsUpdate = true;
        noiseGeometry.setDrawRange(0, newCount);
        noiseParams.count = newCount;
        return;
    }

    noiseParams.count = newCount;
    const positions = new Float32Array(newCount * 3);

    for (let i = 0; i < newCount; i++) {
        const i3 = i * 3;
        const r = noiseClusterRadius;
        const theta = Math.random() * Math.PI * 200;
        const phi = Math.acos(2 * Math.random() - 1);
        positions[i3]     = r * Math.sin(phi) * Math.cos(theta);
        positions[i3 + 1] = r * Math.sin(phi) * Math.sin(theta);
        positions[i3 + 2] = r * Math.cos(phi);
    }

    noiseCache.set(newCount, positions);
    basePositions.set(positions);
    noisePointPositions.set(positions);
    noiseGeometry.attributes.aBasePosition.needsUpdate = true;
    noiseGeometry.attributes.position.needsUpdate = true;
    noiseGeometry.setDrawRange(0, newCount);
}

//===========================================================
//Render Loop Update
//===========================================================
export function updateNoise(time: number, density: number, gain: number, envelope: number) {
    noiseUniforms.uTime.value = time;
    noiseUniforms.uDensity.value = density;
    noiseUniforms.uGain.value = gain;
    noiseUniforms.uEnvelope.value = envelope;
}

const NOISE_ELEMENTS = {
    NOISE_PARAMS: noiseParams,
    NOISE_POSITIONS: noisePointPositions,
    NOISE_POINTS: noisePoints,
    NOISE_GEO: noiseGeometry,
    NOISE_MATERIAL: noiseMaterial,
    NOISE_UNIFORMS: noiseUniforms,
};

export { NOISE_ELEMENTS };



