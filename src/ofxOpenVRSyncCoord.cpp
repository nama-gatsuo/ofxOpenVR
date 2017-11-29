#include "ofxOpenVRSyncCoord.h"

//--------------------------------------------------------------
void ofxOpenVRSyncCoord::setup(string matrix) {
	reset();
	vector<string> a = ofSplitString(matrix, " ");
	if (a.size() >= 16) {
		vector<float> v(16);
		for (int i = 0; i < 16; i++) {
			v[i] = ofToFloat(a[i]);
		}
		matrix_.set(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12], v[13], v[14], v[15]);
	}
}

//--------------------------------------------------------------
string ofxOpenVRSyncCoord::packToString() {			//for saving somethere
	const float *v = matrix_.getPtr();
	string s = "";
	for (int i = 0; i < 16; i++) {
		if (i > 0) s += " ";
		s += ofToString(v[i]);
	}
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
void ofxOpenVRSyncCoord::rotateBy(ofPoint direction, ofPoint origin, float degrees) { //rotate
	ofMatrix4x4 t1, t2;
	ofMatrix4x4 m;
	t1.makeTranslationMatrix(-origin);
	t2.makeTranslationMatrix(origin);
	m.makeRotationMatrix(degrees, direction.x, direction.y, direction.z);
	matrix_ *= t1 * m * t2;
} 

//--------------------------------------------------------------
