#include "Scene.h"

Scene::Scene() :
	name(""),
	length(0.0f),
	b_SetupArd(false),
	ard_port("")
{
	ard = new ofArduino;
}

Scene::~Scene()
{
	ard = new ofArduino;
	delete ard;
}

void Scene::connectArduino()
{
}

void Scene::setupArduino(const int & version)
{
	//	Remove listener because we don't need it anymore
	ofRemoveListener(ard->EInitialized, this, &Scene::setupArduino);

	//	It is now safe to send commands to the Arduino
	b_SetupArd = true;

	//	Print firmware name and version to the console
	ofLogNotice() << ard->getFirmwareName();
	ofLogNotice() << "firmata v" << ard->getMajorFirmwareVersion() << "." << ard->getMinorFirmwareVersion();

	//	Set pin D2 as digital input
	ard->sendDigitalPinMode(2, ARD_INPUT);

	//	Listen for changes on the digital and analog pins
	ofAddListener(ard->EDigitalPinChanged, this, &Scene::digitalPinChanged);
}

void Scene::launchScene()
{
	start_time = ofGetElapsedTimef();
}

void Scene::digitalPinChanged(const int & pin_num)
{
	ofLogNotice("Digital signal received") << "Pin: " << pin_num << " Scene: " << name;
}
