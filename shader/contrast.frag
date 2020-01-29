#version 410
uniform sampler2D tex0;
uniform float contrast0 = 0.2;
uniform float contrast1 = 0.6;
in vec2 texCoordVarying;
out vec4 outputColor;

float mapf(float x, float a, float b, float A, float B) {
	return (x - a) / (b - a)*(B - A) + A;
}

void main()
{
	outputColor = texture(tex0, texCoordVarying);
	float br = (outputColor.r + outputColor.g + outputColor.b) / 3;
	//float br1 = pow(br,0.25);
	float br1 = mapf(br, contrast0, contrast1, 0, 1);
	outputColor *= br1 / br;
}
