#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//	Prints list of valid audio devices
	s_stream.printDeviceList();

	//	Find the MOTU
	vector<ofSoundDevice> s_devices = s_stream.getDeviceList();

	for (int i = 0; i < s_devices.size(); ++i)
	{
		if (s_devices.at(i).name == "MOTU Pro Audio")
		{
			s_device = s_devices.at(i);
			deviceID = i;
			ofLogNotice("Found MOTU") << "Ready for audio";
		}
	}

	//	Make sure we found the MOTU
	if (s_device.name != "MOTU Pro Audio")
	{
		ofLogNotice("Couldn't find the MOTU") << "Not ready for audio";
	}

	//	You can set the device via index or device name
	//s_stream.setDevice(s_device);
	ofModMulti::ofFmodSelectDriver(deviceID);
	
	//	If you need to, set the soundstream settings
	//s_stream.setup(2, 2, 48000, 512, 0);

	//	Load up a sound
	//s_player.load("bell.wav");
	s_player.loadSound("bell.wav");
	//for (int i = 0; i < 4; ++i)
	//{
	//	s_player.setVolumeAt(i, 0.0);
	//}
	//s_player.setVolumeAt(0, 1.0);
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 'p')
	{
		s_player.play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
