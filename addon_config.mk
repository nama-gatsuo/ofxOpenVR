meta:
	ADDON_NAME = ofxOpenVR
	ADDON_DESCRIPTION = Addon to access VR hardware using the OpenVR API from Valve Software
	ADDON_AUTHOR = Hugues Bruyère
	ADDON_TAGS = "VR" "OpenVR" "SteamVR" "HTC Vive" "Oculus Rift"
	ADDON_URL = http://github.com/smallfly/ofxOpenVR

common:

vs:
	ADDON_DLLS_TO_COPY += "libs/openvr/bin/win64/openvr_api.dll"
	ADDON_LIBS += "libs/openvr/lib/win64/openvr_api.lib"
	ADDON_LIBS_EXCLUDE += "libs/openvr/samples/bin"
	ADDON_LIBS_EXCLUDE += "libs/openvr/samples/bin/%"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/bin"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/bin/%"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/lib"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/lib/%"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/src"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/src/%"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/samples"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/samples/%"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/controller_callouts"
	ADDON_INCLUDES_EXCLUDE += "libs/openvr/controller_callouts/%"
	ADDON_SOURCES_EXCLUDE += "libs/openvr/samples"
	ADDON_SOURCES_EXCLUDE += "libs/openvr/samples/%"
	ADDON_SOURCES_EXCLUDE += "libs/openvr/src"
	ADDON_SOURCES_EXCLUDE += "libs/openvr/src/%"
