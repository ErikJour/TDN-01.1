import { juceRelays} from "./juceRelays";

export function initializeFilter(scene, camera) {
    juceRelays.lpfCutoff.valueChangedEvent.addListener(() => {
        const filterCutoffValue = juceRelays.lpfCutoff.getNormalisedValue();
        const normalizedCutoff = filterCutoffValue > 1 ? filterCutoffValue / 100 : filterCutoffValue;
// Fog
        const minLight = 0.002;
        const maxLight = 0.04;
        const invertedIntensity = 1 - normalizedCutoff;
        scene.fog.density = Math.min(maxLight, Math.max(invertedIntensity * maxLight, minLight));
    });

//REZ UPDATES
    juceRelays.lpfResonance.valueChangedEvent.addListener(() => {
        const resonanceValue = juceRelays.lpfResonance.getNormalisedValue();
        camera.position.z = (resonanceValue * -45) + 48;
    });

    //HP Cut UPDATES
    juceRelays.hpfCutoff.valueChangedEvent.addListener(() => {
        const hpValue = juceRelays.hpfCutoff.getNormalisedValue();
    });
}
