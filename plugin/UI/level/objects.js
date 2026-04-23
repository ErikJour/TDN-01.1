import * as THREE from 'three'
import { neutraColorPalette } from '../colors';

//OBJECTS

const textureLoader = new THREE.TextureLoader();
const stainedGlassTextureC = textureLoader.load('textures/stainedGlassWaveB.jpg');

//DAY TWO TEXTURES
const newNoiseTextureA = textureLoader.load('/textures/Greydient4A_texture1_8.jpg')

const levelMaterial = new THREE.MeshStandardMaterial({
    
    color: 'black'});

levelMaterial.map = newNoiseTextureA

const materialTwo = new THREE.MeshStandardMaterial({
    
color: neutraColorPalette.terracotta});

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

export function initializeObjects(scene) {
    //ADD OBJECTS
    const northSphere = createSphere (4, 30, 29);
    northSphere.position.set(0, 22, -50);
    scene.add(northSphere);
    northSphere.material.map = stainedGlassTextureC;

    const southSphere = createSphere (4, 30, 29);
    southSphere.position.set(0, 22, 50);
    scene.add(southSphere);

    const westSphere = createSphere (4, 30, 29);
    westSphere.position.set(-50, 22, 0);
    scene.add(westSphere);

    const eastSphere = createSphere (4, 30, 29);
    eastSphere.position.set(50, 22, 0);
    scene.add(eastSphere);

    scene.add(levelBottomMesh);
    const backWall = createWall(100, 100);
    scene.add(backWall);
    const leftWall = createWall(100, 100);
    scene.add(leftWall);
    const rightWall = createWall(100, 100);
    scene.add(rightWall);
    const frontWall = createWall(100, 100);
    scene.add(frontWall);
    const ceiling = createWall(100, 100);
    scene.add(ceiling);
    levelBottomMesh.position.set(0, -10, 0);
    levelBottomMesh.rotation.x = -Math.PI / 2;
    ceiling.position.set(0, 20, 0);
    ceiling.rotation.x = Math.PI / 2;
    backWall.position.set(0, 0, -50);
    leftWall.rotateY(Math.PI * .5);
    leftWall.position.set(-50, 0, 0);
    rightWall.rotateY(Math.PI * 1.5);
    rightWall.position.set(50, 0, 0);
    frontWall.rotateY(Math.PI);
    frontWall.position.set(0, 0, 50);
}

export { createSphere, levelBottomMesh, createWall };