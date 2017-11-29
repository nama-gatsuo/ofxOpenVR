#pragma once

//Synchronizing coordinate systems of VR and, for example, Kinect's point cloud

#include "ofMain.h"

struct ofxOpenVRSyncCoord {
	void setup(string matrix = "");	//string describing matrix 4x4, a11 a12 ... a
	string packToString();			//for saving somethere

	void applyToGlMatrix();	//set matrix. Normally, you should call ofPushMatrix before this, and ofPopMatrix when you finishing use it

	void reset();							//sets unit matrix
	void moveBy(ofPoint shift);				//move
	void rotateBy(ofPoint direction, ofPoint origin, float degrees); //rotate

	ofMatrix4x4 &matrix() { return matrix_; }
protected:
	ofMatrix4x4 matrix_;
};
