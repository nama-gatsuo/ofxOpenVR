ofxOpenVR 
====================
Implementation of Valve Software's [OpenVR](https://github.com/ValveSoftware/openvr) API.
It's a Kuflex version of ofxOpenVR addon. Forked from smallfly's addon. 

This addon lets create VR applications (using HTC Vive) on openFrameworks, Windows 10.

## Requirements

* HTC Vive (though, it is not required to compile projects, just to deploy)

* Visual Studio 2015

* openFrameworks with GLM (current last version 0.9.8 not work, so use Nightly Build). 
We use of_v20170714_vs_nightly.zip: https://cloud.mail.ru/public/4LrM/WwtFeF6DX

* ofxOpenVR addon folder, which should be placed to openFrameworks/addons/ofxOpenVR. 
Getting addon from Github is a little tricky - it requires also downloading OpenVR 1.0.6, 
and generating projects for examples using Project Generator (and efter excluding CPP files form libs addon's subfolder). 
So you can use this packaged ofxOpenVR addon: https://cloud.mail.ru/public/NBMX/D7thr2h7f  
(note, addon's src folder in this ZIP file is obsolete, so update it from github manually)


After this, compile (in 64 bit) and run addon’s examples located in openFrameworks/addons/ofxOpenVR.
(Please note that to get it working, you need to compile examples in 64 bit mode.)



