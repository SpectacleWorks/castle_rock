#pragma once

#include "ofMain.h"

//	Addons
#include "ofxDmx.h"
#include "ofxMidi.h"

struct Room
{
	string name;
	int midi_channel;
	int dmx_channel;
	int dmx_init_level;
};

class Scene
{
public:
	
	Scene();
	~Scene();

	//*******************************************
	//	Methods
	void setupArduino(const int & version);

	void initScene();
	void launchScene();
	void updateScene();
	void endScene();
	void eStop();
	void lightsOff();

	void updateSeparationRooms();
	void updateUnderwaterRoom();
	void updateInjectionRoom();

	void digitalPinChanged(const int& pin_num);

	//*******************************************
	//	Data
	string name;
	float length;
	int num_rooms;

	float start_time;
	float end_time;
	float run_time;

	bool b_Running;

	//	Rooms
	vector<Room> rooms;

	//	Arduino
	ofArduino* ard;
	bool b_SetupArd;
	string ard_port;

	//	MIDI
	ofxMidiOut* midiOut;
	const int NOTE = 60;		//	C3 in MIDI land
	const int VELOCITY = 100;

	//	DMX
	ofxDmx* dmx;
};