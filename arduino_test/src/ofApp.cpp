#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	Basic OF settings
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	//	Connect the arduino
	ard.connect("COM1", 57600);

	//	Dumb Windows hack to force the Arduino to reset after port is opened
	ard.sendFirmwareVersionRequest();

	//	Listen for EInitialized notification. this indicates that
	//	the arduino is ready to receive commands and it is safe to
	//	call setupArduino()
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArd = false;
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {

	//	Remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);

	//	It is now safe to send commands to the Arduino
	bSetupArd = true;

	//	Print firmware name and version to the console
	ofLogNotice() << ard.getFirmwareName();
	ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

	//	Set pin D2 as digital input
	ard.sendDigitalPinMode(2, ARD_INPUT);

	//	Listen for changes on the digital and analog pins
	ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::update(){

	updateArduino();
}

//--------------------------------------------------------------
void ofApp::updateArduino() {

	//	Update the arduino, get any data or messages (required)
	ard.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);

	ofSetColor(255);
	if (!bSetupArd)
	{
		ofDrawBitmapString("arduino not ready...\n", 40, 40);
	}
	else
	{
		ofDrawBitmapString("Button state: " + button_state, 40, 40);
	}

}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pin_num){

	button_state = "digital pin: " + ofToString(pin_num) + " = " + ofToString(ard.getDigital(pin_num));
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pin_num){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
