ofxOpenVR 
====================
Implementation of Valve Software's [OpenVR](https://github.com/ValveSoftware/openvr) API.


## Requirements

* Visual Studio 2015.

* openFrameworks with GLM (current last version 0.9.8 not work, so use Nightly Build).

## Download
* Ready-to-use ofxOpenVR addon: https://cloud.mail.ru/public/NBMX/D7thr2h7f

* openFrameworks of_v20170714_vs_nightly.zip: https://cloud.mail.ru/public/4LrM/WwtFeF6DX


## Usage


1. If you download this archive directly (without Git) - then also download OpenVR from Git, 1.0.6

2. Create an openframeworks' project using the Project Generator (and exclude .CPP files from ofxOpenVR/libs/openvr subfolders), or add the addon's source files and the OpenVR headers to your existing project.

(3. In `Property Manager` (open it from `View -> Other Windows -> Property Manager`), right click on your project to select `Add Existing Property Sheet...` and select the `ofxOpenVR.props` file. )

## Notes
Tested with the HTC Vive and the Oculus Rift (consumer version) on Windows 10.

