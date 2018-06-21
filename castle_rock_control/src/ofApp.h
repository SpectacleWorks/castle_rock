#pragma once

#include "ofMain.h"

//	Addons
#include "ofxMidi.h"
#include "ofxXmlSettings.h"

//	Global variables
const int NOTE = 60;		//	C3 in MIDI land
const int VELOCITY = 64;

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	void exit();

	void loadMidiSettings();

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

	//	XML Settings
	ofxXmlSettings xml_midi_settings;
	
	//	Sounds & MIDI
	int num_channels;
	string midi_port;
	map<string, int> midi_settings; // room, midi channel
	ofxMidiOut midiOut;

};
