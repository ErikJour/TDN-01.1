import * as THREE from 'three'
import { neutraColorPalette } from './colors';

//SPOTLIGHTS
function createSpotlight(x, y, z, intensity)
{
const spotlight = new THREE.SpotLight(neutraColorPalette.terracotta, intensity);
spotlight.position.set(x, y, z);
spotlight.castShadow = true;
return spotlight;
}

//AMBIENT LIGHT
const ambientLightA = new THREE.AmbientLight(neutraColorPalette.warmGray, 2);
ambientLightA.position.set(0, 0, 10);

export { createSpotlight, ambientLightA };
