import * as THREE from 'three'

const levelTopGeometry = new THREE.SphereGeometry(19, 30, 16, 0, 6, 2.5, 2);

const levelMaterial = new THREE.MeshStandardMaterial();

const levelTopMesh = new THREE.Mesh(levelTopGeometry, levelMaterial);

const levelBottomGeometry = new THREE.PlaneGeometry( 1, 1 );

const levelBottomMesh = new THREE.Mesh(levelBottomGeometry, levelMaterial);

export {levelTopMesh, levelBottomMesh };

