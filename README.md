ofxOpenVR 
====================
Implementation of Valve Software's [OpenVR](https://github.com/ValveSoftware/openvr) API.
This addon lets create VR applications (using HTC Vive) on openFrameworks, Windows 10. It's forked from smallfly's addon. 

The most important fix comparing original version is about 
problem of one eye's vertical shift due matrices computations errors.
There are also many smaller improvements, for example, draw_... function for fastest rendering left eye's scene on the screen without additional computations.

## Requirements

* HTC Vive (though, it is not required to compile projects, just to deploy)

* Visual Studio 2017

* openFrameworks 10.1

* ofxOpenVR addon folder, which should be placed to openFrameworks/addons/ofxOpenVR. 

## Using addon

* To check all is working, compile and run addon’s examples located 
in **openFrameworks/addons/ofxOpenVR**.
Note, examples are tested in 64-bit mode and as they contain 64-bit version of **openvr_api.dll**.

* In your own projects, create the project using **Project Generator**, and
copy **openvr_api.dll** file to the **bin** folder of the project from **copy_to_bin** addon's folder.


