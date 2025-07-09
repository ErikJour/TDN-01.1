import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//OBJECTS

const textureLoader = new THREE.TextureLoader();
const stainedGlassTextureC = textureLoader.load('textures/stainedGlassWaveB.jpg');
const sineTextureB = textureLoader.load('textures/Greydient4A_texture1_5.jpg');
const triangleTextureA = textureLoader.load('textures/Greydient4B_texture1_6.jpg');
const squareTextureA = textureLoader.load('textures/Greydient4C_texture1_3.jpg');
const noiseTextureA = textureLoader.load('textures/Greydient4A_texture1_8.jpg');
const noiseTextureB = textureLoader.load('textures/Greydient4A_texture1_11.jpg');
const noiseTextureC = textureLoader.load('textures/Greydient4A_texture1_16.jpg');



// const sphereGeo = new THREE.SphereGeometry(4, 30, 29);

const levelMaterial = new THREE.MeshMatcapMaterial({
    
    color: neutraColorPalette.charcoalGray});
    levelMaterial.map = stainedGlassTextureC

const materialTwo = new THREE.MeshStandardMaterial({
    
    color: neutraColorPalette.terracotta});

// const sphereMesh = new THREE.Mesh(sphereGeo, materialTwo);

function createSphere (radius, width, height) 
{
    const sphereGeo = new THREE.SphereGeometry(radius, width, height);
    const sphereMesh = new THREE.Mesh(sphereGeo, materialTwo);
    sphereMesh.material.map = stainedGlassTextureC;

    return sphereMesh;

}

function createWall(width, height) 
{

    const wallGeometry = new THREE.PlaneGeometry(width, height);
    const wallMesh = new THREE.Mesh(wallGeometry, levelMaterial);

    return wallMesh;
}

const levelBottomGeometry = new THREE.PlaneGeometry( 100, 100 );

const levelBottomMesh = new THREE.Mesh(levelBottomGeometry, levelMaterial);

export { createSphere, levelBottomMesh, createWall };