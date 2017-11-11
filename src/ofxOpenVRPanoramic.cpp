#include "ofxOpenVRPanoramic.h"

#ifndef STRINGIFY
#define STRINGIFY(A) #A 
#endif

//--------------------------------------------------------------
ofxOpenVRPanoramic::ofxOpenVRPanoramic() {
	inited_ = false;
}

//--------------------------------------------------------------
void ofxOpenVRPanoramic::setup(ofxOpenVR &openVR, string imageFileName, float sphere_rad){
	ofSetVerticalSync(false);

	cout << "For ofxOpenVRPanoramic we need to call ofDisableArbTex(), so we do it..." << endl;
	ofDisableArbTex();

	openVR_ = &openVR;

	image_.load(imageFileName);
	sphere_.set(sphere_rad, 10);
	sphere_.setPosition(glm::vec3(.0f, .0f, .0f));

	//Shader setup
	//shader_.load("sphericalProjection");

	// Vertex shader source
	string vertex = "#version 150\n";
	vertex += STRINGIFY(
	uniform mat4 modelViewProjectionMatrix;
	uniform mat4 normalMatrix;

	in vec4 position;
	in vec4 normal;

	out vec4 modelNormal;

	void main() {
		modelNormal = normal;
		gl_Position = modelViewProjectionMatrix * position;

	}
	);

	// Fragment shader source
	string fragment = "#version 150\n";
	fragment += STRINGIFY(	
	uniform sampler2D tex0;
	in vec4	modelNormal;
	out vec4 fragColor;

	const float ONE_OVER_PI = 1.0 / 3.14159265;

	void main() {
		vec3 normal = normalize(modelNormal.xyz);
		// spherical projection based on the surface normal
		vec2 coord = vec2(0.5 + 0.5 * atan(normal.x, -normal.z) * ONE_OVER_PI, acos(normal.y) * ONE_OVER_PI);
		fragColor = texture(tex0, coord);
	}
	);

	// Shader
	shader_.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
	shader_.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
	shader_.bindDefaults();
	shader_.linkProgram();

	inited_ = true;
	
}

//--------------------------------------------------------------
void ofxOpenVRPanoramic::loadImage(string imageFileName) {
	image_.load(imageFileName);
}

//--------------------------------------------------------------
void  ofxOpenVRPanoramic::draw() {
	if (!inited_) return;

	ofSetColor(ofColor::white);

	shader_.begin();
	shader_.setUniformTexture("tex0", image_, 1);
	sphere_.draw();
	shader_.end();
}

//--------------------------------------------------------------
