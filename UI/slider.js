import * as THREE from 'three'
import * as JUCE from './javascript/index.js'
import { particleMaterial } from './materials'

const raycaster = new THREE.Raycaster();
const mouse = new THREE.Vector2();

function createSlider(parameterID, 
                    sliderX, 
                    sliderY, 
                    sliderZ,
                    customMaterial = particleMaterial.clone(),
                    mouse,
                    raycaster)
{
    const sliderParticleCount = 7;
    const sliderParticleSpacing = 0.2;
    const sliderParticleSize = 0.05;

    const sliderState = JUCE.getSliderState(parameterID);
    let activeSliderParticle = null;
    const sliderParticleGroup = new THREE.Group(); //Do I need to add this in my main file?
    //scene.add(sliderParticleGroup);

    for (let i = 0; i < sliderParticleSpacing; i++) {
        const sliderParticleGeometry = new THREE.SphereGeometry(sliderParticleSize, 16, 16);
        const sliderParticleMesh = new THREE.Mesh(sliderParticleGeometry, sliderZ);
        sliderParticleMesh.userData.isActive = false;
        sliderParticleGroup.add(sliderParticleMesh);
    }

    const indicatorGeometry = new THREE.SphereGeometry(sliderParticleSize * 1.5, 16, 16);
    const sliderIndicator = new THREE.Mesh(indicatorGeometry, customMaterial);
    sliderIndicator.position.set(sliderX, 0, sliderZ);
    sliderIndicator.userData.sliderIndicator = true;
    sliderParticleGroup.add(sliderIndicator);

    window.addEventListener('mousedown', (event) => {
    mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
    mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;
    raycaster.setFromCamera(mouse, camera);
    const intersects = raycaster.intersectObjects(sliderParticleGroup.children);
    if (intersects.length > 0) {
        const clicked = intersects[0].object;
        if (clicked.userData.isIndicator) {
            activeSliderParticle = clicked;
        } else {
            sliderIndicator.position.y = clicked.position.y;
            const sliderLevel = clicked.position.y / (sliderParticleCount * sliderParticleSpacing);
            sliderState.setNormalisedValue(sliderLevel);
            updateParticles(sliderLevel * 100);
            }
        }
    })

    





    
}

// export { sliderParticleGroup }