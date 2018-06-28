#pragma once

#include "ofMain.h"

struct Room
{
	string name;
	int midi_channel;
};

class Scene
{
public:
	
	Scene();
	~Scene();

	//*******************************************
	//	Methods
	void connectArduino();
	void setupArduino(const int & version);

	void launchScene();

	void digitalPinChanged(const int& pin_num);

	//*******************************************
	//	Data
	string name;
	float length;
	int num_rooms;

	float start_time;
	float run_time;

	//	Rooms
	vector<Room> rooms;

	//	Arduino
	ofArduino* ard;
	bool b_SetupArd;
	string ard_port;
};