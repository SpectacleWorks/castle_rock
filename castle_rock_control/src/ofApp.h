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
const vector<int> LOOPED_MIDI = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

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
	void setupGUI();
	void initArduinos();

	//	Updates
	void updateArduinos();
	void hardStop();
	void restart();

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

	void sendMidiOn(const int& channel);
	void sendMidiOff(const int& channel);

	//	MIDI Toggle Listeners
	void toggled_01(bool& on);
	void toggled_02(bool& on);
	void toggled_03(bool& on);
	void toggled_04(bool& on);
	void toggled_05(bool& on);
	void toggled_06(bool& on);
	void toggled_07(bool& on);
	void toggled_08(bool& on);
	void toggled_09(bool& on);
	void toggled_10(bool& on);
	void toggled_11(bool& on);
	void toggled_12(bool& on);
	void toggled_13(bool& on);
	void toggled_14(bool& on);
	void toggled_15(bool& on);
	void toggled_16(bool& on);

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
	void drawGUI();
	
	ofxPanel midi_panel;
	vector<ofxToggle> midi_toggles;
};
