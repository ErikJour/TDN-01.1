import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//OBJECTS

const textureLoader = new THREE.TextureLoader();
const stainedGlassTextureC = textureLoader.load('textures/stainedGlassWaveB.jpg');

//DAY TWO TEXTURES
const newNoiseTextureA = textureLoader.load('textures/AdobeStock_682864478_Preview.jpeg')
const newNoiseTextureB = textureLoader.load('textures/AdobeStock_846456489_Preview.jpeg')
const newNoiseTextureC = textureLoader.load('textures/AdobeStock_927583757_Preview.jpeg')
const newNoiseTextureD = textureLoader.load('textures/AdobeStock_1163812336_Preview.jpeg')
const newNoiseTextureE = textureLoader.load('textures/AdobeStock_1237336418_Preview.jpeg')
const newNoiseTextureF = textureLoader.load('textures/AdobeStock_1243109284_Preview.jpeg')
const newNoiseTextureG = textureLoader.load('textures/AdobeStock_1249128757_Preview.jpeg')
const newNoiseTextureH = textureLoader.load('textures/AdobeStock_1335294749_Preview.jpeg')
const newNoiseTextureI = textureLoader.load('textures/AdobeStock_1335294749_Preview.jpeg')

//MATCAPS
const matcapB = textureLoader.load('matcaps/0_export_6.png');
const matcapA = textureLoader.load('matcaps/0_export_25.png')
const matcapC = textureLoader.load('matcaps/1C70C6_09294C_0F3F73_52B3F6-512px.png')
const matcapD = textureLoader.load('matcaps/4A6442_D0AB75_81CD94_181B12-512px.png')

const levelMaterial = new THREE.MeshMatcapMaterial({
    
    color: neutraColorPalette.oliveBrown});

levelMaterial.map = stainedGlassTextureC
levelMaterial.matcap = matcapC

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