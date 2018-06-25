#pragma once

#include "ofMain.h"

//	Core OF
#include "ofEvents.h"

//	Addons
#include "ofxMidi.h"
#include "ofxXmlSettings.h"

//	Project Headers
#include "Scene.h"

//	Global variables
const int NOTE = 60;		//	C3 in MIDI land
const int VELOCITY = 64;

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	void exit();

	//	Setup
	void loadSceneSettings();
	void setupMIDI();
	void initArduinos();

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
	ofxXmlSettings scene_settings;
	
	//	Sounds & MIDI
	string midi_port;
	ofxMidiOut midiOut;

	//	Scenes
	vector<Scene*> scenes;
	int num_scenes;
	int num_arduinos;

	ofArduino ard;
	vector<ofArduino> ards;
	bool bSetupArd;

	void setupArduino(const int& version);
	void digitalPinChanged(const int& pin_num);
	void analogPinChanged(const int& pin_num);
	void updateArduino();
};
