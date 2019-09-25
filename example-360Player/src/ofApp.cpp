//Modified example for panoramic player by Kuflex, 2017
// Thanks to @num3ric for sharing this:
// http://discourse.libcinder.org/t/360-vr-video-player-for-ios-in-cinder/294/6

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofDisableArbTex(); //required for using "sampler2D" instead "sampler2DRect" in shaders

	// We need to pass the method we want ofxOpenVR to call when rending the scene
	openVR.setup(std::bind(&ofApp::render, this, std::placeholders::_1));

	pano.setup(openVR, "DSCN0143.JPG");

	bShowHelp = true;
}

//--------------------------------------------------------------
void ofApp::exit() {
	openVR.exit();
}

//--------------------------------------------------------------
void ofApp::update(){
	openVR.update();
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
		_strHelp << "Drag and drop a 360 spherical (equirectangular) image to load it in the player. " << endl;
		_strHelp << "Toggle OpenVR mirror window (press: m)." << endl;
		ofDrawBitmapStringHighlight(_strHelp.str(), ofPoint(10.0f, 20.0f), ofColor(ofColor::black, 100.0f));
	}
}

//--------------------------------------------------------------
void  ofApp::render(vr::Hmd_Eye nEye) {

	openVR.pushMatricesForRender(nEye);

	pano.draw();

	openVR.popMatricesForRender();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		case 'h':
			bShowHelp = !bShowHelp;
			break;

		case 'm':
			openVR.toggleMirrorWindow();
			break;

		default:
			break;
	}
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
void ofApp::dragEvent(ofDragInfo dragInfo) {
	//TODO: Why do we need to parse the path to replace the \ by / in order to work?
	std::string path = dragInfo.files[0];
	std::replace(path.begin(), path.end(), '\\', '/');

	pano.image().load(path);
	pano.image().update();
}
