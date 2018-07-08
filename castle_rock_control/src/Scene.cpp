#include "Scene.h"

//--------------------------------------------------------------
Scene::Scene() :
	name(""),
	length(0.0f),
	start_time(0.0f),
	run_time(0.0f),
	b_Running(false),
	b_SetupArd(false),
	ard_port("")
{
}

//--------------------------------------------------------------
Scene::~Scene()
{
}

//--------------------------------------------------------------
void Scene::setupArduino(const int & version)
{
	//	Remove listener because we don't need it anymore
	ofRemoveListener(ard->EInitialized, this, &Scene::setupArduino);

	//	It is now safe to send commands to the Arduino
	b_SetupArd = true;

	//	Print firmware name and version to the console
	ofLogNotice() << ard->getFirmwareName();
	ofLogNotice() << "firmata v" << ard->getMajorFirmwareVersion() << "." << ard->getMinorFirmwareVersion();

	//	Set pin D2 as digital output, pin D3 as digital input
	ard->sendDigitalPinMode(2, ARD_OUTPUT);
	ard->sendDigitalPinMode(3, ARD_INPUT);

	//	Set initial pin states
	ard->sendDigital(2, 0, true);

	//	Listen for changes on the digital and analog pins
	ofAddListener(ard->EDigitalPinChanged, this, &Scene::digitalPinChanged);
}

//--------------------------------------------------------------
void Scene::initScene()
{
	//	Set intial light levels
	for (int i = 0; i < rooms.size(); ++i)
	{
		for (int j = 0; j < rooms.at(i)->dmx_map.size(); ++j)
		{
			int channel = rooms.at(i)->dmx_channels.at(j);
			dmx->setLevel(channel, rooms.at(i)->dmx_map.at(channel));
		}
	}
	dmx->update();
}

//--------------------------------------------------------------
void Scene::launchScene()
{
	//	Set start time at which scene is launched
	start_time = ofGetElapsedTimef();

	//	Set scene status to running
	b_Running = true;

	//	Launch MIDI
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (rooms.at(i)->midi_channel != 0)
		{
			midiOut->sendNoteOn(rooms.at(i)->midi_channel, NOTE, VELOCITY);
		}
	}

	//	Print to console
	ofLogNotice("Scene launched") << name;
}

//--------------------------------------------------------------
void Scene::updateScene()
{
	// Don't try to update the scene if it's not running
	if (!b_Running)
	{
		if (name == "separation")
		{
			if (ofGetElapsedTimef() - end_time > 10)
			{
				ard->sendDigital(2, 0, true);
			}
			else
			{
				ard->sendDigital(2, 1, true);
			}
		}
		return;
	}

	//	Update the run time
	run_time = ofGetElapsedTimef() - start_time;

	//	End the scene if run time has exceeded the scene length
	if (run_time >= length)
	{
		endScene();
		return;
	}

	//	Route update functions by scenne name
	if (name == "separation")
	{
		updateSeparationRooms();
	}
	else if (name == "underwater")
	{
		updateUnderwaterRoom();
	}
	else if (name == "injection")
	{
		updateInjectionRoom();
	}

	//	Print to console
	//ofLogNotice("Scene running") << name;
}

//--------------------------------------------------------------
void Scene::endScene()
{
	//	Set scene status to not running
	b_Running = false;
	
	//	Get the end time
	end_time = ofGetElapsedTimef();

	//	Unlock doors for separation rooms
	if (name == "separation")
	{
		ard->sendDigital(2, 1, true);
		//ofLogNotice("Updating separation scene -> pin 2") << "1";
	}

	//	Send any necessary MIDI note off messages
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (rooms.at(i)->midi_channel != 0)
		{
			midiOut->sendNoteOff(rooms.at(i)->midi_channel, NOTE, 0);
		}
	}
	
	//	Force pin D2 to low state
	ard->sendDigital(2, 0, true);
	//ofLogNotice("Updating pin 2") << "0";

	//	Print to console
	ofLogNotice("Scene ending") << name;
}

//--------------------------------------------------------------
void Scene::eStop(){

	//	Set pin 2 to LOW (opens doors)
	ard->sendDigital(2, 0, true);

	//	Set light levels to max brightness
	for (int i = 0; i < rooms.size(); ++i)
	{
		for (int j = 0; j < rooms.at(i)->dmx_channels.size(); ++j)
		{
			int channel = rooms.at(i)->dmx_channels.at(j);
			dmx->setLevel(channel, 255);
		}
	}
	dmx->update();
}

//--------------------------------------------------------------
void Scene::lightsOff()
{
	//	Set light levels to zero
	for (int i = 0; i < rooms.size(); ++i)
	{
		for (int j = 0; j < rooms.at(i)->dmx_channels.size(); ++j)
		{
			int channel = rooms.at(i)->dmx_channels.at(j);
			dmx->setLevel(channel, 0);
		}
	}
	dmx->update();
}

//--------------------------------------------------------------
void Scene::digitalPinChanged(const int & pin_num)
{
	ofLogNotice("Digital signal received") << "Pin: " << pin_num << " State: " << ard->getDigital(pin_num) << " Scene: " << name;

	if (pin_num == 3 && ard->getDigital(pin_num) == 1)
	{
		if (!b_Running)
			launchScene();
		else
			ofLogWarning("Scene already running") << name;
	}
}

//--------------------------------------------------------------
void Scene::updateSeparationRooms()
{
	//	Make sure magnets are on
	if (ard->getDigital(2) != 0)
	{
		ard->sendDigital(2, 0, true);
		//ofLogNotice("Updating separation scenes -> pin 2") << "0";
	}

	//	Update lights
	updateItLights();
	updateShiningLights();
	

	dmx->update();
	
}

//--------------------------------------------------------------
void Scene::updateUnderwaterRoom()
{
	if (ard->getDigital(2) != 1)
	{
		ard->sendDigital(2, 1, true);
		//ofLogNotice("Updating underwater scene -> pin 2") << "1";
	}
}

//--------------------------------------------------------------
void Scene::updateInjectionRoom()
{
	if (ard->getDigital(2) != 1)
	{
		ard->sendDigital(2, 1, true);
		//ofLogNotice("Updating injection scene -> pin 2") << "1";
	}
}

void Scene::updateItLights()
{
	if (run_time < 20)
	{
		dmx->setLevel(IT_DRAIN_DMX, 16);
		dmx->setLevel(IT_CEILING_DMX, 0);
	}
	else if (run_time > 20 && run_time < 50)
	{
		int level = ofMap(run_time, 20, 50, 16, 127);
		dmx->setLevel(IT_DRAIN_DMX, level);
		dmx->setLevel(IT_CEILING_DMX, 0);
	}
	else if (run_time > 50 && run_time < 80)
	{
		dmx->setLevel(IT_DRAIN_DMX, 127);
		dmx->setLevel(IT_CEILING_DMX, 0);
	}
	else if (run_time > 80 && run_time < 100)
	{
		dmx->setLevel(IT_DRAIN_DMX, 0);
		dmx->setLevel(IT_CEILING_DMX, 127);
	}
	else
	{
		int level = ofMap(run_time, 100, 120, 0, 16);
		dmx->setLevel(IT_DRAIN_DMX, level);
		level = ofMap(run_time, 100, 120, 127, 0);
		dmx->setLevel(IT_CEILING_DMX, level);
	}
}

void Scene::updateShiningLights()
{
	if (run_time < 20)
	{
		dmx->setLevel(SHINING_DMX, 64);
	}
	else if (run_time > 20 && run_time < 100)
	{
		int level = ofMap(run_time, 20, 100, 64, 32);
		dmx->setLevel(SHINING_DMX, level);
	}
	else
	{
		dmx->setLevel(SHINING_DMX, 0);
	}
}

void Scene::updateShawshankLights()
{
	if (run_time < 20)
	{
		dmx->setLevel(SHAWSHANK_DMX, 64);
	}
	else if (run_time > 20 && run_time < 100)
	{
		int level = ofMap(run_time, 20, 100, 64, 32);
		dmx->setLevel(SHAWSHANK_DMX, level);
	}
	else
	{
		dmx->setLevel(SHAWSHANK_DMX, 0);
	}
}
