#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	Test connection to DMX interface
	bool b_connect = dmx.connect("COM5");

	if (b_connect)
	{
		ofLogNotice("Connected") << "DMX ready";
	}

	//	Set initial levels

	chan1.set("Channel 1", 120, 0, 255);
	chan2.set("Channel 2", 120, 0, 255);
	chan3.set("Channel 3", 120, 0, 255);
	chan4.set("Channel 4", 120, 0, 255);
	chan5.set("Channel 5", 120, 0, 255);
	chan6.set("Channel 6", 120, 0, 255);
	chan7.set("Channel 7", 120, 0, 255);
	chan8.set("Channel 8", 120, 0, 255);

	panel.setName("Panel");
	panel.setup();
	panel.add(chan1);
	panel.add(chan2);
	panel.add(chan3);
	panel.add(chan4);
	panel.add(chan5);
	panel.add(chan6);
	panel.add(chan7);
	panel.add(chan8);
}

//--------------------------------------------------------------
void ofApp::update(){
	dmx.setLevel(1, chan1);
	dmx.setLevel(2, chan2);
	dmx.setLevel(3, chan3);
	dmx.setLevel(4, chan4);
	dmx.setLevel(5, chan5);
	dmx.setLevel(6, chan6);
	dmx.setLevel(7, chan7);
	dmx.setLevel(8, chan8);
	dmx.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofSetColor(0);
	//ofDrawBitmapString(ofToString(level), 20, 20);

	panel.draw();
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
	}
	else if (key == OF_KEY_DOWN)
	{
		level -= 10;
		if (level < 0) level = 0;
		dmx.setLevel(1, level);
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
