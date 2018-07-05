#pragma once

#include "ofMain.h"

//	Addons
#include "ofxDmx.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	ofxDmx dmx;
	int level;

	ofxPanel panel;
	ofParameter<int> chan1;
	ofParameter<int> chan2;
	ofParameter<int> chan3;
	ofParameter<int> chan4;
	ofParameter<int> chan5;
	ofParameter<int> chan6;
	ofParameter<int> chan7;
	ofParameter<int> chan8;
};
