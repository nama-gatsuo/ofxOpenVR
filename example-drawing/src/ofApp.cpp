#include "ofApp.h"

#define STRINGIFY(A) #A

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);

	bShowHelp = true;
	bUseShader = true;		//Rendering with and without shaders should give the same result, so check it by pressing Space
	bIsLeftTriggerPressed = false;
	bIsRightTriggerPressed = false;

	polylineResolution = .004f;
	lastLeftControllerPosition.set(ofVec3f());
	lastRightControllerPosition.set(ofVec3f());

	// We need to pass the method we want ofxOpenVR to call when rending the scene
	openVR.setup(std::bind(&ofApp::render, this, std::placeholders::_1));
	openVR.setDrawControllers(true);

	// Vertex shader source
	string vertex;

	vertex = "#version 150\n";
	vertex += STRINGIFY(
						uniform mat4 matrix;

						in vec4 position;

						void main() {
							gl_Position = matrix * position;
						}
						);

	// Fragment shader source
	string fragment = "#version 150\n";
	fragment += STRINGIFY(
						out vec4 outputColor;
						void main() {
							outputColor = vec4(1.0, 1.0, 1.0, 1.0);
						}
						);

	// Shader
	shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
	shader.bindDefaults();
	shader.linkProgram();
}

//--------------------------------------------------------------
void ofApp::exit(){
	openVR.exit();
}

//--------------------------------------------------------------
void ofApp::update(){
	openVR.update();
	while (openVR.hasControllerEvents()) {
		ofxOpenVRControllerEvent event;
		openVR.getNextControllerEvent(event);
		controllerEvent(event);
	}

	if (bIsLeftTriggerPressed) {
		if (openVR.isControllerConnected(0)) {
			// Getting the translation component of the controller pose matrix
			leftControllerPosition = openVR.getControllerCenter(0);

			if (lastLeftControllerPosition.distance(leftControllerPosition) >= polylineResolution) {
				leftControllerPolylines[leftControllerPolylines.size() - 1].lineTo(leftControllerPosition);
				lastLeftControllerPosition.set(leftControllerPosition);
			}
		}
	}

	if (bIsRightTriggerPressed) {
		if (openVR.isControllerConnected(1)) {
			// Getting the translation component of the controller pose matrix
			rightControllerPosition = openVR.getControllerCenter(1);

			if (lastRightControllerPosition.distance(rightControllerPosition) >= polylineResolution) {
				rightControllerPolylines[rightControllerPolylines.size() - 1].lineTo(rightControllerPosition);
				lastRightControllerPosition = rightControllerPosition;
			}
		}
	}
	
	openVR.render();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//openVR.renderDistortion();
	openVR.renderScene(vr::Eye_Left);
	//openVR.draw_using_contrast_shader(ofGetWidth(), ofGetHeight());

	openVR.drawDebugInfo(10.0f, 500.0f);

	// Help
	if (bShowHelp) {
		_strHelp.str("");
		_strHelp.clear();
		_strHelp << "HELP (press h to toggle): " << endl;
		_strHelp << "Press the Trigger of a controller to draw a line with that specific controller." << endl;
		_strHelp << "Press the Touchpad to star a new line." << endl;
		_strHelp << "Press the Grip button to clear all the lines drawn with that specific controller." << endl;
		_strHelp << "Drawing resolution " << polylineResolution << " (press: +/-)." << endl;
		_strHelp << "Drawing default 3D models " << openVR.getRenderModelForTrackedDevices() << " (press: m)." << endl;
		_strHelp << "Using shader (' '):  " << ((bUseShader) ? "TRUE" : "FALSE") << endl;
		
		ofDrawBitmapStringHighlight(_strHelp.str(), ofPoint(10.0f, 20.0f), ofColor(ofColor::black, 100.0f));
	}
}

//--------------------------------------------------------------
void  ofApp::render(vr::Hmd_Eye nEye){
	// Using a shader
	if (bUseShader) {
		ofMatrix4x4 currentViewProjectionMatrix = openVR.getCurrentViewProjectionMatrix(nEye);

		shader.begin();
		shader.setUniformMatrix4f("matrix", currentViewProjectionMatrix, 1);
		ofSetColor(ofColor::white);
		for (auto pl : leftControllerPolylines) {
			pl.draw();
		}

		for (auto pl : rightControllerPolylines) {
			pl.draw();
		}
		shader.end();
	}
	// Loading matrices
	else {
		//Prepare matrices for VR rendering
		//Note, this function also calls openVR.flipVr(), 
		//so some rendering may be flipped.
		//For 2D rendering in FBO you can call openVR.flipOf(), 
		//and then restore the mode back by calling openVR.flipVr().
		openVR.pushMatricesForRender(nEye);



		ofSetColor(ofColor::white);

		for (auto pl : leftControllerPolylines) {
			pl.draw();
		}

		for (auto pl : rightControllerPolylines) {
			pl.draw();
		}
		
		openVR.popMatricesForRender();
	}
}

//--------------------------------------------------------------
void ofApp::controllerEvent(ofxOpenVRControllerEvent& args){
	cout << "ofApp::controllerEvent > role: " << ofToString(int(args.controllerRole)) 
		<< " - event type: " << ofToString(int(args.eventType)) 
		<< " - button type: " << ofToString(int(args.buttonType))
		<< " - x: " << args.analogInput_xAxis 
		<< " - y: " << args.analogInput_yAxis << endl;
	// Left
	if (args.controllerRole == ControllerRole::Left) {
		// Trigger
		if (args.buttonType == ButtonType::ButtonTrigger) {
			if (args.eventType == EventType::ButtonPress) {
				bIsLeftTriggerPressed = true;

				if (leftControllerPolylines.size() == 0) {
					leftControllerPolylines.push_back(ofPolyline());
					lastLeftControllerPosition.set(ofVec3f());
				}
			}
			else if (args.eventType == EventType::ButtonUnpress) {
				bIsLeftTriggerPressed = false;
			}
		}
		// ButtonTouchpad
		else if (args.buttonType == ButtonType::ButtonTouchpad) {
			if (args.eventType == EventType::ButtonPress) {
				leftControllerPolylines.push_back(ofPolyline());
				lastLeftControllerPosition.set(ofVec3f());
			}
		}
		// Grip
		else if (args.buttonType == ButtonType::ButtonGrip) {
			if (args.eventType == EventType::ButtonPress) {
				for (auto pl : leftControllerPolylines) {
					pl.clear();
				}

				leftControllerPolylines.clear();
			}
		}
	}

	// Right
	else if (args.controllerRole == ControllerRole::Right) {
		// Trigger
		if (args.buttonType == ButtonType::ButtonTrigger) {
			if (args.eventType == EventType::ButtonPress) {
				bIsRightTriggerPressed = true;

				if (rightControllerPolylines.size() == 0) {
					rightControllerPolylines.push_back(ofPolyline());
					lastRightControllerPosition.set(ofVec3f());
				}
			}
			else if (args.eventType == EventType::ButtonUnpress) {
				bIsRightTriggerPressed = false;
			}
		}
		// ButtonTouchpad
		else if (args.buttonType == ButtonType::ButtonTouchpad) {
			if (args.eventType == EventType::ButtonPress) {
				rightControllerPolylines.push_back(ofPolyline());
				lastRightControllerPosition.set(ofVec3f());
			}
		}
		// Grip
		else if (args.buttonType == ButtonType::ButtonGrip) {
			if (args.eventType == EventType::ButtonPress) {
				for (auto pl : rightControllerPolylines) {
					pl.clear();
				}

				rightControllerPolylines.clear();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case '+':
		case '=':
			polylineResolution += .0001f;
			break;
		
		case '-':
		case '_':
			polylineResolution -= .0001f;
			if (polylineResolution < 0) {
				polylineResolution = 0;
			}
			break;

		case 'h':
			bShowHelp = !bShowHelp;
			break;

		case 'm':
			openVR.setRenderModelForTrackedDevices(!openVR.getRenderModelForTrackedDevices());
			break;

		case ' ':
			bUseShader = !bUseShader;	//switch shaders. The result should be the same
			break;

		default:
			break;
	}

	cout << polylineResolution  << endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
