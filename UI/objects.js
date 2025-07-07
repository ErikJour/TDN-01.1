import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//OBJECTS


// const sphereGeo = new THREE.SphereGeometry(4, 30, 29);

const levelMaterial = new THREE.MeshStandardMaterial({
    
    color: neutraColorPalette.charcoalGray});

const materialTwo = new THREE.MeshStandardMaterial({
    
    color: neutraColorPalette.terracotta});

// const sphereMesh = new THREE.Mesh(sphereGeo, materialTwo);

function createSphere (radius, width, height) 
{
    const sphereGeo = new THREE.SphereGeometry(radius, width, height);
    const sphereMesh = new THREE.Mesh(sphereGeo, materialTwo);

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