import * as THREE from 'three'
import { FontLoader } from 'three/examples/jsm/loaders/FontLoader.js'
import { TextGeometry } from 'three/examples/jsm/geometries/TextGeometry.js';
import { neutraColorPalette } from './colors';

let lfoWord;

const labelMaterial = new THREE.MeshStandardMaterial({
    color: neutraColorPalette.terracotta, 
    opacity: 0.0,   
    transparent: true,
    roughness: 0.5,  
    metalness: 0.1  
});

const fontLoader = new FontLoader();
fontLoader.load("fonts/P22 FLLW Exhibition_Regular.json", function(font) {

    function createLetter(letter, font){
    return new TextGeometry(letter, {
         font: font,
        size: 11,
        height: 2,
        curveSegments: 12,
        bevelEnabled: true,
        bevelThickness: .1,
        bevelSize: 0.5,
        bevelOffset: 0,
        bevelSegments: 5
    });

}

const labelSize = 0.08;

function createLabel (xPos, yPos, zPos, word)
{
const wordGeometry = createLetter(word, font);
wordGeometry.computeBoundingBox();
console.log(wordGeometry.boundingBox);
const wordMesh = new THREE.Mesh(wordGeometry, labelMaterial);
wordMesh.position.set(xPos, yPos, zPos);
wordMesh.scale.set(labelSize, labelSize, labelSize * .25)
wordMesh.rotation.x = Math.PI / 2; 
wordMesh.castShadow = true;
wordMesh.receiveShadow = true;
wordMesh.transparent = true;
scene.add(wordMesh);
return { wordMesh };
}

const lfoWordX = -2.8;
const lfoWordY = 7.5;
const lfoWordZ = -64.3;
lfoWord = createLabel (lfoWordX, lfoWordY, lfoWordZ, 'LFO');

});

