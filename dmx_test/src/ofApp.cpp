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
	chan9.set("Channel 9", 120, 0, 255);
	chan10.set("Channel 10", 120, 0, 255);
	chan11.set("Channel 11", 120, 0, 255);
	chan12.set("Channel 12", 120, 0, 255);
	chan13.set("Channel 13", 120, 0, 255);
	chan14.set("Channel 14", 120, 0, 255);
	chan15.set("Channel 15", 120, 0, 255);
	chan16.set("Channel 16", 120, 0, 255);

	chan17.set("Channel 17", 120, 0, 255);
	chan18.set("Channel 18", 120, 0, 255);
	chan19.set("Channel 19", 120, 0, 255);
	chan20.set("Channel 20", 120, 0, 255);
	chan21.set("Channel 21", 120, 0, 255);
	chan22.set("Channel 22", 120, 0, 255);
	chan23.set("Channel 23", 120, 0, 255);
	chan24.set("Channel 24", 120, 0, 255);
	chan25.set("Channel 25", 120, 0, 255);
	chan26.set("Channel 26", 120, 0, 255);
	chan27.set("Channel 27", 120, 0, 255);
	chan28.set("Channel 28", 120, 0, 255);
	chan29.set("Channel 29", 120, 0, 255);
	chan30.set("Channel 30", 120, 0, 255);
	chan31.set("Channel 31", 120, 0, 255);
	chan32.set("Channel 32", 120, 0, 255);

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
	panel.add(chan9);
	panel.add(chan10);
	panel.add(chan11);
	panel.add(chan12);
	panel.add(chan13);
	panel.add(chan14);
	panel.add(chan15);
	panel.add(chan16);

	panel.add(chan17);
	panel.add(chan18);
	panel.add(chan19);
	panel.add(chan20);
	panel.add(chan21);
	panel.add(chan22);
	panel.add(chan23);
	panel.add(chan24);
	panel.add(chan25);
	panel.add(chan26);
	panel.add(chan27);
	panel.add(chan28);
	panel.add(chan29);
	panel.add(chan30);
	panel.add(chan31);
	panel.add(chan32);
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
	dmx.setLevel(9, chan9);
	dmx.setLevel(10, chan10);
	dmx.setLevel(11, chan11);
	dmx.setLevel(12, chan12);
	dmx.setLevel(13, chan13);
	dmx.setLevel(14, chan14);
	dmx.setLevel(15, chan15);
	dmx.setLevel(16, chan16);

	dmx.setLevel(17, chan17);
	dmx.setLevel(18, chan18);
	dmx.setLevel(19, chan19);
	dmx.setLevel(20, chan20);
	dmx.setLevel(21, chan21);
	dmx.setLevel(22, chan22);
	dmx.setLevel(23, chan23);
	dmx.setLevel(24, chan24);
	dmx.setLevel(25, chan25);
	dmx.setLevel(26, chan26);
	dmx.setLevel(27, chan27);
	dmx.setLevel(28, chan28);
	dmx.setLevel(29, chan29);
	dmx.setLevel(30, chan30);
	dmx.setLevel(31, chan31);
	dmx.setLevel(32, chan32);
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
