#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	Test connection to DMX interface
	bool b_connect = dmx.connect("COM5");

	if (b_connect)
	{
		ofLogNotice("Connected") << "DMX ready";
	}

	//	Set initial level to zero
	level = 127;
	dmx.setLevel(1, level);
}

//--------------------------------------------------------------
void ofApp::update(){

	dmx.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0);
	ofDrawBitmapString(ofToString(level), 20, 20);
}

//--------------------------------------------------------------
void ofApp::exit() {
	dmx.clear();
	dmx.update(true);
	dmx.disconnect();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_UP)
	{
		level += 10;
		if (level > 255) level = 255;
		dmx.setLevel(1, level);
		dmx.update();
	}
	else if (key == OF_KEY_DOWN)
	{
		level -= 10;
		if (level < 0) level = 0;
		dmx.setLevel(1, level);
		dmx.update();
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
