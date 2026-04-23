uniform vec3 uColor;
uniform vec3 uColorGrey;
uniform float uGain;
uniform float uEnvelope;

uniform vec3 uLightPos1;
uniform vec3 uLightColor1;
uniform vec3 uLightPos2;
uniform vec3 uLightColor2;
varying vec3 vWorldPos;

varying float vAlpha;
varying float vId;

void main() {

    vec2 uv = gl_PointCoord - 0.5;
    float dist = length(uv);
    float angle = atan(uv.y, uv.x);

    // Organic irregular edge — each particle unique via vId
    float warp = 0.03 * sin(angle * 3.0 + vId * 6.2831)
    + 0.02 * sin(angle * 7.0 + vId * 3.14)
    + 0.015 * sin(angle * 13.0 - vId * 9.42);

    // Soft spore edge
    float innerRadius = 0.25 + warp;
    float outerRadius = 0.42 + warp;
    float shape = 1.0 - smoothstep(innerRadius, outerRadius, dist);

    // Subtle inner glow — brighter at center
    float core = 1.0 - smoothstep(0.0, 0.2, dist);
    shape += core * 0.3 * uEnvelope;

    if (shape < 0.01) discard;

    vec3 color = mix(uColorGrey, uColor, uGain);

    // Distance-based light pickup
    float d1 = length(vWorldPos - uLightPos1);
    float atten1 = 1.0 / (1.0 + d1 * 0.5 + d1 * d1 * 0.1);
    float d2 = length(vWorldPos - uLightPos2);
    float atten2 = 1.0 / (1.0 + d2 * 0.5 + d2 * d2 * 0.1);

    vec3 litColor = color
    + uLightColor1 * atten1 * 0.4
    + uLightColor2 * atten2 * 0.4;

    gl_FragColor = vec4(litColor, shape * vAlpha);

}
