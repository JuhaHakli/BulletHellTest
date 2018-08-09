#version 150

in vec2 texCoord;
in float fTint;
flat in int fTime;

out vec4 outColor;

uniform sampler2D tex;

vec4 rgb2hsv(vec4 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec4(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x, c.w);
}

vec4 hsv2rgb(vec4 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	vec3 step =  c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    return vec4(step.x, step.y, step.z, c.w);
}

void main()
{
	float newTime = fTime;
	vec4 fragColor = texture(tex, texCoord);
	
	vec4 inHsv = rgb2hsv(fragColor);
	
	inHsv = vec4(fTint, inHsv.y+(sin(newTime/2.0f)/6.0f), inHsv.z+(sin(newTime/2.0f)/6.0f), inHsv.w);
	
	outColor = hsv2rgb(inHsv);
	outColor = vec4(outColor.x, outColor.y, outColor.z, outColor.w); 
}