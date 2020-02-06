#pragma once

#include "ofMain.h"
#include <openvr.h>
#include "CGLRenderModel.h"

/*
ofxOpenVR addon, adopted by Kuflex, 2017
- Enchanced controllers support
	float t0 = openVR.getTriggerState(0);
	float t1 = openVR.getTriggerState(1);
	cout << "trigger " << t0 << " " << t1 << endl;

	ofPoint p0 = openVR.getTrackPadState(0);
	ofPoint p1 = openVR.getTrackPadState(1);
	cout << "trackpad " << p0.x << ", " << p0.y << "   " << p1.x << ", " << p1.y << endl;

- Added ofxOpenVRPanoramic module for 360 panorama environment rendering, see ofxOpenVRPanoramic.h for details
*/

//--------------------------------------------------------------
//--------------------------------------------------------------
enum class ControllerRole
{
	Left = 0,
	Right = 1,
	Unknown = 3
};

//--------------------------------------------------------------
enum class EventType
{
	ButtonPress = 0,
	ButtonUnpress = 1,
	ButtonTouch = 2,
	ButtonUntouch = 3
};

//--------------------------------------------------------------
enum class ButtonType
{
	ButtonSystem = 0,
	ButtonApplicationMenu = 1,
	ButtonGrip = 2,
	ButtonTouchpad = 3,
	ButtonTrigger = 4
};

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxOpenVRControllerEvent
{
public:
	ControllerRole controllerRole;
	ButtonType buttonType;
	EventType eventType;
	float analogInput_xAxis;
	float analogInput_yAxis;
};

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxOpenVR {

public:
	void setup(std::function< void(vr::Hmd_Eye) > f);
	void exit();

	void update();

	//---- Setting up rendering matrices, for drawing without shaders
	//Prepare matrices for VR rendering
	//Note, this function also calls openVR.flipVr(), 
	//so some rendering may be flipped.
	//For 2D rendering in FBO you can call openVR.flipOf(), 
	//and then restore the mode back by calling openVR.flipVr().
	//(For currently unknown reason, flipping of matrix in oF causes inaccuracy on rendering VR,
	//So this function discards this flipping by calling setFlipVr() )
	void pushMatricesForRender(vr::Hmd_Eye nEye); 

	//This function restores matrices after rendering. 
	//Note: Also it resets orientation mode by calling setFlipOf()
	void popMatricesForRender();

	//---- rendering the whole scene
	void render();				//This is the MAIN rendering function to draw into HDM, you may call call it in update()
								//Also it fills buffers, which are used by renderDistortion() and draw()
	void renderDistortion();	//Can be called after render(), renders distorted stereo picture on the screen
	void renderScene(vr::Hmd_Eye nEye); //renders image for each eye, direct calling for drawing on screen 
							//can reduce your app performance, so please use draw() instead.

	//Render left eye (prepared buffer) on the screen - faster than calling renderScene 
	//render() must be called before draw()
	//NOTE: currently size of rendering texture is limited render_width,render_heigth (SOME BUG)
	void draw_using_contrast_shader(float w, float h, float contrast0 = 0, float contrast1 = 1, int eye = vr::Eye_Left);
	void draw_using_binded_shader(float w, float h, int eye = vr::Eye_Left);	//for custom shader drawing, see create_contrast_shader() for example

	void setRenderModelForTrackedDevices(bool bRender);		
	bool getRenderModelForTrackedDevices();


	//---- debug output
	void drawDebugInfo(float x = 10.0f, float y = 20.0f);

	//HMD
	glm::mat4x4 getHDMPose();
	glm::vec3 getHDMCenter();
	glm::vec3 getHDMAxe(int axe);	//axe 0,1,2 - OX,OY,OZ result is normalized
	
	glm::mat4x4 getHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	glm::mat4x4 getHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	glm::mat4x4 getCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	glm::mat4x4 getCurrentProjectionMatrix(vr::Hmd_Eye nEye);
	glm::mat4x4 getCurrentViewMatrix(vr::Hmd_Eye nEye);

	void setClearColor(ofFloatColor color);

	void showMirrorWindow();
	void hideMirrorWindow();
	void toggleMirrorWindow();

	void toggleCamera() {
		isCameraShown = !isCameraShown;
	}

	void toggleGrid(float transitionDuration = 2.0f);
	void showGrid(float transitionDuration = 2.0f);
	void hideGrid(float transitionDuration = 2.0f);

	//---- Controllers
	int controllersCount() { return 2; }
	bool isControllerConnected(int controller);
	void setDrawControllers(bool bDrawControllers);

	glm::mat4x4 getControllerPose(int controller);	//controller 0 - left, 1 - right
	glm::vec3 getControllerCenter(int controller);
	glm::vec3 getControllerAxe(int controller, int axe);	//axe 0,1,2 - OX,OY,OZ result is normalized
	float getTriggerState(int controller);	//0..1
	glm::vec3 getTrackPadState(int controller); //if touched[-1..1]x[-1..1], else (-1000,-1000). 
	//Note, at the touch start, there are 2-3 frames this function returns values near to (0,0).

	//Controllers events. Note: the queue of events is cleared at each update call.
	bool hasControllerEvents();
	bool getNextControllerEvent(ofxOpenVRControllerEvent &event);

	//---- Convert i to left/right type
	vr::ETrackedControllerRole toControllerRole(int controller);	//0 - left, 1 - right
	vr::Hmd_Eye toEye(int i);	//0 - left, 1 - right
	int toDeviceId(int controller);

	//---- Get center and axes from a matrix
	static glm::vec3 get_center(const glm::mat4x4& pose);
	static glm::vec3 get_axe(const glm::mat4x4& pose, int axe);	//axe 0,1,2 - OX,OY,OZ result is normalized

	//Size of rendering port for each eye
	int render_width() { return _nRenderWidth; }
	int render_height() { return _nRenderHeight; }

	const ofTexture& getCameraTexture() const {
		return cameraImg.getTexture();
	}

protected:
	vector<ofxOpenVRControllerEvent> controller_events_;


	struct VertexDataScene
	{
		glm::vec3 position;
		glm::vec2 texCoord;
	};

	struct VertexDataLens
	{
		glm::vec2 position;
		glm::vec2 texCoordRed;
		glm::vec2 texCoordGreen;
		glm::vec2 texCoordBlue;
	};

	std::array<ofFbo, 2> eyeFbo;

	std::function< void(vr::Hmd_Eye) > _callableRenderFunction;

	bool _bIsGLInit;
	bool _bIsGridVisible;
	
	ofFloatColor _clearColor;
	uint32_t _nRenderWidth, _nRenderHeight;

	ofParameter<float> nearClip, farClip;
	
	vr::IVRSystem *_pHMD;
	
	bool startVideo();
	void closeVideo();

	vr::IVRTrackedCamera * trackedCamera;
	vr::TrackedCameraHandle_t trackedCameraHandle;
	uint32_t m_nCameraFrameWidth;
	uint32_t m_nCameraFrameHeight;
	uint32_t m_nCameraFrameBufferSize;
	uint8_t * m_pCameraFrameBuffer;
	uint32_t m_nLastFrameSequence;
	int frameCounter;
	ofImage cameraImg;
	std::array<ofFbo, 2> camFbo;

	vr::IVRRenderModels *_pRenderModels;
	std::string _strTrackingSystemName;
	std::string _strTrackingSystemModelNumber;
	vr::TrackedDevicePose_t _rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	glm::mat4x4 _rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	int _iTrackedControllerCount;
	int _iTrackedControllerCount_Last;
	int _iValidPoseCount;
	int _iValidPoseCount_Last;

	std::ostringstream _strPoseClassesOSS;

	ofShader _lensShader;
	GLuint _unLensVAO;
	GLuint _glIDVertBuffer;
	GLuint _glIDIndexBuffer;
	unsigned int _uiIndexSize;

	glm::mat4x4 _mat4HMDPose_world;	//for using this pose in world rendering

	glm::mat4x4 _mat4HMDPose;
	std::array<glm::mat4, 2> _mat4eyePos;

	glm::mat4x4 _mat4ProjectionCenter;
	std::array<glm::mat4, 2> _mat4Projection;

	int _leftControllerDeviceID;
	int _rightControllerDeviceID;
	glm::mat4x4 _mat4LeftControllerPose;
	glm::mat4x4 _mat4RightControllerPose;

	bool _bDrawControllers;
	ofVboMesh _controllersVbo;
	ofShader _controllersTransformShader;

	bool init();
	bool initGL();
	bool initCompositor();

	bool createAllShaders();
	bool createFrameBuffer(int nWidth, int nHeight, vr::Hmd_Eye eye);

	bool setupStereoRenderTargets();
	void setupDistortion();
	void setupCameras();

	void updateDevicesMatrixPose();
	void handleInput();
	void processVREvent(const vr::VREvent_t & event);

	void renderStereoTargets();
	
	void drawControllers();

	glm::mat4x4 convertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);

	bool _bRenderModelForTrackedDevices;
	ofShader _renderModelsShader;
	CGLRenderModel* findOrLoadRenderModel(const char *pchRenderModelName);
	void setupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackedDeviceIndex);
	void setupRenderModels();

	std::vector< CGLRenderModel * > _vecRenderModels;
	CGLRenderModel *_rTrackedDeviceToRenderModel[vr::k_unMaxTrackedDeviceCount];

	ofShader contrast_shader_;	//shader used in draw_using_contrast_shader
	bool isCameraShown;
};
