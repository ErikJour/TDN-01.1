
uniform float uTime;
uniform float uDensity;
uniform float uGain;
uniform float uEnvelope;
uniform float uPointSize;
uniform float uPixelRatio;

attribute vec3 aBasePosition;

varying float vAlpha;
varying float vId;
varying vec3 vWorldPos;

float hash(vec3 p) {
    return fract(sin(dot(p, vec3(127.1, 311.7, 74.7))) * 43758.5453);
}

void main() {

    vec3 pos = aBasePosition;
    float id = hash(aBasePosition);
    vId = id;

    // Density: morph the radius
    float radiusScale = mix(0.2, 2.0, uDensity);
    pos *= radiusScale;

    // Envelope: directional drift
    vec3 dir = normalize(aBasePosition + 0.001);
    float envPush = uEnvelope * 0.2;
    pos += dir * envPush;

    // Time-based wobble modulated by envelope
    float speed = 0.3 + id * 0.7;
    float wobble = sin(uTime * speed + id * 6.2831) * 0.05;
    pos += dir * wobble * (0.3 + uEnvelope * 0.7);

    vWorldPos = (modelMatrix * vec4(pos, 1.0)).xyz;

    vec4 mvPosition = modelViewMatrix * vec4(pos, 1.0);

    // Point size — envelope only
    float sizeBase = uPointSize * uPixelRatio * 100.0;
    float envSize = 1.0 + uEnvelope * 0.8;
    gl_PointSize = sizeBase * envSize / -mvPosition.z;

    gl_Position = projectionMatrix * mvPosition;

    vAlpha = (0.4 + 0.6 * uEnvelope);
    vAlpha *= 0.5 + 0.5 * id;
}

