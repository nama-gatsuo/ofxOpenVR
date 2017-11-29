#include "ofxOpenVRSyncCoord.h"

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::setup(string matrix) {
	reset();
}

//--------------------------------------------------------------
string ofxOpenVRSyncCoord::packToString() {			//for saving somethere
	string s = "";
	return s;
}

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::applyToGlMatrix() {	//set matrix. Normally, you should call ofPushMatrix before this, and ofPopMatrix when you finishing use it
	//	void decompose( ofVec3f& translation,
	//ofQuaternion& rotation,
//		ofVec3f& scale,
		//ofQuaternion& so ) const;
	ofMultMatrix(matrix_);

}

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::reset() {							//sets unit matrix
	matrix_.makeIdentityMatrix();
}

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::moveBy(ofPoint shift) {				//move
	ofMatrix4x4 m;
	m.makeTranslationMatrix(shift);
	matrix_ *= m;
}

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::rotateBy(ofPoint vec, float degrees) { //rotate
	ofMatrix4x4 m;
	m.makeRotationMatrix(degrees, vec.x, vec.y, vec.z);
	matrix_ *= m;
}

//--------------------------------------------------------------
