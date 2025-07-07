import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//SPOTLIGHTS
const spotLightA = new THREE.SpotLight(neutraColorPalette.terracotta, 20);
spotLightA.position.set(1, 5, -45);
spotLightA.intensity = 2000;
// spotLightA.angle = Math.PI;
spotLightA.castShadow = true;

function createSpotlight(x, y, z, intensity)
{
const spotlight = new THREE.SpotLight(neutraColorPalette.terracotta, intensity);
spotlight.position.set(x, y, z);
// spotlight.intensity = 2000;
// spotLightA.angle = Math.PI;
spotlight.castShadow = true;

return spotlight;
}

//AMBIENT LIGHT
const ambientLightA = new THREE.AmbientLight(neutraColorPalette.warmGray, 5);
ambientLightA.position.set(0, 0, 10);

//DIRECTIONAL LIGHT
const directionalLight = new THREE.DirectionalLight(0xffffff, .5)
directionalLight.position.set(0, 20, 0)

export { createSpotlight, ambientLightA, directionalLight };
