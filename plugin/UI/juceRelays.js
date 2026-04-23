import {neutraColorPalette} from "./colors";
import {generateNoiseParticles, NOISE_ELEMENTS} from "./noise/noiseParticlesNew";

export const juceRelays = {
    noiseVol: null,
    noiseType: null,
    lpfCutoff: null,
    lpfResonance: null,
    hpfCutoff: null
};


export function initializeJuceRelays(Juce) {
        juceRelays.noiseType = Juce.getToggleState("noiseType");
        juceRelays.noiseVol = Juce.getSliderState("globalGain");
        juceRelays.lpfCutoff = Juce.getSliderState("lpCutoff");
        juceRelays.lpfResonance = Juce.getSliderState("lpResonance");
        juceRelays.hpfCutoff = Juce.getSliderState("hpCutoff");

    //==========================================================================
    // Noise Viz Update
    //==========================================================================
    generateNoiseParticles(500);

    juceRelays.noiseType.valueChangedEvent.addListener(() => {

        const noiseTypeValue = juceRelays.noiseType.getValue();
        console.log(noiseTypeValue);

        if (noiseTypeValue === false) {

            console.log('Setting color to white');
            NOISE_ELEMENTS.NOISE_UNIFORMS.uColor.value.set(neutraColorPalette.neutraCream);
        }

        else if (noiseTypeValue === true) {
            console.log('Setting color to pink');

            NOISE_ELEMENTS.NOISE_UNIFORMS.uColor.value.set(neutraColorPalette.neutraPink);

        }
    })

    juceRelays.noiseVol.valueChangedEvent.addListener(() => {

        const globalGainValue = juceRelays.noiseVol.getNormalisedValue();
        console.log("Global gain: ", globalGainValue);
        generateNoiseParticles((globalGainValue * 100000)+ 500);
    })

        return juceRelays;
}