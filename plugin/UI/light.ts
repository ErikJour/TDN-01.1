import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//SPOTLIGHTS
function createSpotlight(x: number, y: number, z: number, intensity: number)
{
const spotlight = new THREE.SpotLight(neutraColorPalette.terracotta, intensity);
spotlight.position.set(x, y, z);
spotlight.castShadow = true;
return spotlight;
}

//AMBIENT LIGHT
const ambientLightA = new THREE.AmbientLight(neutraColorPalette.warmGray, 2);
ambientLightA.position.set(0, 0, 10);

export function initializeLights(scene: THREE.Scene) {
    // ADD LIGHTS
    const spotlightNorth = createSpotlight(0, 10, -50, 1000);
    scene.add(spotlightNorth);
    const spotlightSouth = createSpotlight(0, 10, 50, 1000);
    scene.add(spotlightSouth);
    const spotlightWest = createSpotlight(-50, 10, 0, 1000);
    scene.add(spotlightWest);
    const spotlightEast = createSpotlight(50, 10, 0, 1000);
    scene.add(spotlightEast);
    scene.add(ambientLightA);
    ambientLightA.intensity = 9;
    //Fog
// const desaturatedTunnel = new THREE.Color(tunnelColor).lerp(new THREE.Color(0x808080), 0.1);
    scene.fog = new THREE.FogExp2(neutraColorPalette.mutedTeal, 0.03);
}

export { createSpotlight, ambientLightA };
