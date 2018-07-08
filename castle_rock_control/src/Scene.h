#pragma once

#include "ofMain.h"

//	Addons
#include "ofxDmx.h"
#include "ofxMidi.h"

//	Constants
const int IT_DRAIN_DMX		= 1;
const int IT_CEILING_DMX	= 2;
const int SHINING_DMX		= 3;
const int SHAWSHANK_DMX		= 4;

struct Room
{
	string name;
	int midi_channel;
	map<int, int> dmx_map;
	vector<int> dmx_channels;
	//int dmx_channel;
	//int dmx_init_level;
};

class Scene
{
public:
	
	Scene();
	~Scene();

	//*******************************************
	//	Methods
	void setupArduino(const int & version);

	virtual void initScene();
	virtual void launchScene();
	virtual void updateScene();
	virtual void endScene();

	void eStop();
	void lightsOff();

	void updateSeparationRooms();
	void updateUnderwaterRoom();
	void updateInjectionRoom();

	void updateItLights();
	void updateShiningLights();
	void updateShawshankLights();

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
	vector<Room*> rooms;
	map<string, Room*> room_map;

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