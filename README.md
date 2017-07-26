ofxOpenVR 
====================
Implementation of Valve Software's [OpenVR](https://github.com/ValveSoftware/openvr) API.
Forked from smallfly's addon. 

This addon lets create VR applications (using HTC Vive) on openFrameworks, Windows 10.

## Requirements

* HTC Vive (to compile projects it is not required)

* Visual Studio 2015.

* openFrameworks with GLM (current last version 0.9.8 not work, so use Nightly Build). We use of_v20170714_vs_nightly.zip: https://cloud.mail.ru/public/4LrM/WwtFeF6DX

* ofxOpenVR addon folder, which should be placed to openFrameworks/addons/ofxOpenVR. Getting addon from Github is a little tricky - it requires also downloading OpenVR 1.0.6, and generating projects for examples using Project Generator (and efter excluding CPP files form libs addon's subfolder). So you can use this packaged ofxOpenVR addon: https://cloud.mail.ru/public/NBMX/D7thr2h7f


After this, compile and run three addon’s examples located in openFrameworks/addons/ofxOpenVR.



