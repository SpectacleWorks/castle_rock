#pragma once

#include "ofMain.h"

//	Core OF
#include "ofEvents.h"

//	Addons
#include "ofxDmx.h"
#include "ofxGui.h"
#include "ofxMidi.h"
#include "ofxXmlSettings.h"

//	Project Headers
#include "Scene.h"

//	Global variables
const int NOTE = 60;		//	C3 in MIDI land
const int VELOCITY = 64;

class ofApp : public ofBaseApp{

public:

	//*******************************************
	//	Members
	void setup();
	void update();
	void draw();
	void exit();

	//	Setup
	void loadSceneSettings();
	void setupMIDI();
	void setupDMX();
	void initArduinos();

	//	Updates
	void updateArduinos();

	//	Events
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

	//*******************************************
	//	Data

	//	XML Settings
	ofxXmlSettings scene_settings;
	
	//	Sounds & MIDI
	string midi_port;
	ofxMidiOut midiOut;

	//	Scenes
	vector<Scene*> scenes;
	map<string, Scene*> scene_map;
	int num_scenes;
	int num_arduinos;

	//	Arduinos
	vector<ofArduino*> ards;
	
	//	DMX
	string dmx_port;
	ofxDmx dmx;

	//	GUI


	//void setupArduino(const int& version);
	//void digitalPinChanged(const int& pin_num);
	//void analogPinChanged(const int& pin_num);
	
};
