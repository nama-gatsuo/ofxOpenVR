#include "ofxOpenVRPanoramic.h"

#define STRINGIFY(A) #A 

//--------------------------------------------------------------
void ofxOpenVRPanoramic::setup(ofxOpenVR &openVR, string imageFileName){
	ofSetVerticalSync(false);

	cout << "For ofxOpenVRPanoramic we need to call ofDisableArbTex(), so we do it..." << endl;
	ofDisableArbTex();

	openVR_ = &openVR;

	image_.load(imageFileName);
	sphere_.set(10, 10);
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
	
}

//--------------------------------------------------------------
void  ofxOpenVRPanoramic::render(vr::Hmd_Eye nEye) {

	ofPushView();
	ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadMatrix(openVR_->getCurrentProjectionMatrix(nEye));
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofMatrix4x4 currentViewMatrixInvertY = openVR_->getCurrentViewMatrix(nEye);
	currentViewMatrixInvertY.scale(1.0f, -1.0f, 1.0f);
	ofLoadMatrix(currentViewMatrixInvertY);

	ofSetColor(ofColor::white);

	shader_.begin();
	shader_.setUniformTexture("tex0", image_, 1);
	sphere_.draw();
	shader_.end();

	ofPopView();

}

//--------------------------------------------------------------
