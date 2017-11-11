#pragma once

#include "ofMain.h"
#include "ofxOpenVR.h"

/*
	360 spherical panoramic render by Kuflex, 2017.

	Based on example-360Player of original ofxOpenVR addon.
	Thanks to @num3ric for sharing this:
	http://discourse.libcinder.org/t/360-vr-video-player-for-ios-in-cinder/294/6

	Note:
	To work, this module calls ofDisableArbTex() at setup()

	Usage:
	Place "panorama.jpg" to bin/data folder (or any other image)

	//------------ ofApp.h ---------------
	#pragma once

	#include "ofMain.h"
	#include "ofxOpenVR.h"
	#include "ofxOpenVRPanoramic.h"

	class ofApp : public ofBaseApp{

	public:
	void setup();
	void exit();

	void update();
	void draw();

	void render(vr::Hmd_Eye nEye);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOpenVR openVR;
	ofxOpenVRPanoramic pano;
	};

	//------------ ofApp.cpp ---------------
	void ofApp::setup(){
		ofSetVerticalSync(false);
		openVR.setup(std::bind(&ofApp::render, this, std::placeholders::_1));
		pano.setup(openVR, "panorama.jpg");				//Loading image
	}

	void ofApp::exit() {
		openVR.exit();
	}

	void ofApp::update() {
		openVR.update();
	}

	void ofApp::draw() {
		openVR.render();
		openVR.renderScene(vr::Eye_Left);
		openVR.drawDebugInfo(10.0f, 500.0f);
	}
	void  ofApp::render(vr::Hmd_Eye nEye) {
		openVR.pushMatricesForRender(nEye);
		pano.draw();
		openVR.popMatricesForRender();
	}
	*/


class ofxOpenVRPanoramic {
public:
	ofxOpenVRPanoramic();
	void setup(ofxOpenVR &openVR, string imageFileName, float sphere_rad=20.0);
	void loadImage(string imageFileName);
	void draw();
	ofImage &image() { return image_; }
	bool isInitialized() { return inited_; }
protected:
	bool inited_;
	ofImage image_;
	ofShader shader_;
	ofSpherePrimitive sphere_;

	ofxOpenVR *openVR_;
};
