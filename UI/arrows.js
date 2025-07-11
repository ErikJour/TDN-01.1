import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//NAVIGATION ARROW============================================================================================================
const arrowGroup = new THREE.Group();
const arrowWidth = 0.05;;
const arrowHeight = 0.0466;
const arrowDepth = 0.001;
const arrowRadius = 0.0025;
const arrowSmoothness = 4;

function createRoundedTriangleGeometry(width, height, depth, radius, smoothness) {
    const triangleShape = new THREE.Shape();
    const triangleEpsilon = 0.00001;
    const radius0 = radius - triangleEpsilon;
    const halfWidth = width / 2;

    triangleShape.moveTo(-halfWidth + radius0, -height / 2);
    triangleShape.lineTo(halfWidth - radius0, -height / 2);
    triangleShape.quadraticCurveTo(halfWidth, -height / 2, halfWidth, -height / 2 + radius0);
    triangleShape.lineTo(radius0, height / 2 - radius0);
    triangleShape.quadraticCurveTo(0, height / 2, -radius0, height / 2 - radius0);
    triangleShape.lineTo(-halfWidth, -height / 2 + radius0);
    triangleShape.quadraticCurveTo(-halfWidth, -height / 2, -halfWidth + radius0, -height / 2);

    const extrudeSettings = {
        steps: 1,
        depth: depth,
        bevelEnabled: true,
        bevelThickness: radius,
        bevelSize: radius,
        bevelSegments: smoothness
    };
    const geometry = new THREE.ExtrudeGeometry(triangleShape, extrudeSettings);
    geometry.center();
    return geometry;
}

const arrowMaterialUp = new THREE.MeshBasicMaterial({
    color: neutraColorPalette.sageGreen 
})
const arrowMaterialDown = new THREE.MeshBasicMaterial({
    color: neutraColorPalette.sageGreen 
})
const arrowMaterialLeft = new THREE.MeshBasicMaterial({
    color: neutraColorPalette.sageGreen 
})
const arrowMaterialRight = new THREE.MeshBasicMaterial({
    color: neutraColorPalette.sageGreen 
})

function createArrow(material = arrowMaterialUp) {
    const arrow = new THREE.Group();
    const headGeometry = createRoundedTriangleGeometry(arrowWidth, arrowHeight, arrowDepth, arrowRadius, arrowSmoothness);
    const head = new THREE.Mesh(headGeometry, material);
    head.position.y = 0;
    arrow.add(head);

    return arrow;
}

const arrowGeometry = createRoundedTriangleGeometry(arrowWidth, arrowHeight, arrowDepth, arrowRadius, arrowSmoothness);
const arrowMesh = new THREE.Mesh(arrowGeometry, arrowMaterialUp);

const arrowOffsetX = 0.15;
const arrowOffsetY = -0.035;
const arrowZ = -0.25;
const arrowScale = 0.15;
const offset = 0.0105; 

const arrowUp = createArrow(arrowMaterialUp);
arrowUp.scale.set(arrowScale, arrowScale, arrowScale);
arrowUp.position.set(arrowOffsetX, arrowOffsetY + offset, arrowZ);

const arrowDown = createArrow(arrowMaterialDown);
arrowDown.rotation.z = Math.PI;
arrowDown.scale.set(arrowScale, arrowScale, arrowScale);
arrowDown.position.set(arrowOffsetX, arrowOffsetY - offset, arrowZ);

const arrowLeft = createArrow(arrowMaterialLeft);
arrowLeft.rotation.z = Math.PI * 0.5;
arrowLeft.scale.set(arrowScale, arrowScale, arrowScale);
arrowLeft.position.set(arrowOffsetX - offset, arrowOffsetY, arrowZ);

const arrowRight = createArrow(arrowMaterialRight);
arrowRight.rotation.z = Math.PI * 1.5;
arrowRight.scale.set(arrowScale, arrowScale, arrowScale);
arrowRight.position.set(arrowOffsetX + offset, arrowOffsetY, arrowZ);

// Final group positioning
arrowGroup.visible = true;


export { arrowUp, arrowDown, arrowLeft, arrowRight, arrowGroup }