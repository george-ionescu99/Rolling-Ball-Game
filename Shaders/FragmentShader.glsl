#version 330



uniform vec2 u_resolution;
uniform float time;
uniform int deform;

varying float noise;
varying float factor;

// TODO: get color value from vertex shader
in vec3 color;
//in vec3 outVS_floor_color;

//layout(location = 0) out vec4 out_color;


float random( vec3 scale, float seed ){
  return fract( sin( dot( gl_FragCoord.xyz + seed, scale ) ) * 43758.5453 + seed ) ;
}

vec3 rainbow(float x)
{
	/*
		Target colors
		=============
		
		L  x   color
		0  0.0 vec4(1.0, 0.0, 0.0, 1.0);
		1  0.2 vec4(1.0, 0.5, 0.0, 1.0);
		2  0.4 vec4(1.0, 1.0, 0.0, 1.0);
		3  0.6 vec4(0.0, 0.5, 0.0, 1.0);
		4  0.8 vec4(0.0, 0.0, 1.0, 1.0);
		5  1.0 vec4(0.5, 0.0, 0.5, 1.0);
	*/
	
	float level = floor(x * 6.0);
	float r = float(level <= 2.0) + float(level > 4.0) * 0.5;
	float g = max(1.0 - abs(level - 2.0) * 0.5, 0.0);
	float b = (1.0 - (level - 4.0) * 0.5) * float(level >= 4.0);
	return vec3(r, g, b);
}

vec3 colorA = vec3(0.349,0.141,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);

void main()
{
	// TODO: write pixel out color
	if(deform == 0) {
        gl_FragColor = vec4(color, 1);
    }
    else {
		vec3 color = vec3(0.0);

		float pct = abs(sin(time));

		// Mix uses pct (a value from 0-1) to
		// mix the two colors
		color = mix(colorA, colorB, pct);

		gl_FragColor = vec4(color,1.0);
    }
}