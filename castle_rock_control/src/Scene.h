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

	void digitalPinChanged(const int& pin_num);

	//*******************************************	
	//	Data
	string name;
	float length;
	int num_rooms;

	//	Rooms
	vector<Room> rooms;

	//	Arduino
	ofArduino* ard;
	bool b_SetupArd;
	string ard_port;
};