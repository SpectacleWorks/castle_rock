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
	ofParameter<int> chan9;
	ofParameter<int> chan10;
	ofParameter<int> chan11;
	ofParameter<int> chan12;
	ofParameter<int> chan13;
	ofParameter<int> chan14;
	ofParameter<int> chan15;
	ofParameter<int> chan16;

	ofParameter<int> chan17;
	ofParameter<int> chan18;
	ofParameter<int> chan19;
	ofParameter<int> chan20;
	ofParameter<int> chan21;
	ofParameter<int> chan22;
	ofParameter<int> chan23;
	ofParameter<int> chan24;
	ofParameter<int> chan25;
	ofParameter<int> chan26;
	ofParameter<int> chan27;
	ofParameter<int> chan28;
	ofParameter<int> chan29;
	ofParameter<int> chan30;
	ofParameter<int> chan31;
	ofParameter<int> chan32;
};
