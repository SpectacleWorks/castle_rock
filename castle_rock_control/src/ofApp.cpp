#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	OF Settings
	ofBackground(0);
	ofSetFrameRate(30);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);

	//	Read in XML settings
	loadSceneSettings();
	//	Connect to MIDI port
	setupMIDI();
	//	Connect to DMX interface
	setupDMX();
	//	Initialize arduinos
	initArduinos();
	//	Initialize scenes
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->initScene();
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	updateArduinos();

	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->updateScene();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit(){

	// clean up
	midiOut.closePort();

	//	lights off
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->lightsOff();
	}
}

//--------------------------------------------------------------
void ofApp::loadSceneSettings()
{
	//	Load general settings
	scene_settings.loadFile("scene_settings.xml");
	midi_port = scene_settings.getValue("general:midi_port_name", "");
	dmx_port = scene_settings.getValue("general:dmx_port", "");
	num_scenes = scene_settings.getValue("general:num_scenes", 0);
	num_arduinos = scene_settings.getValue("general:num_arduinos", 0);

	if (midi_port == "" || dmx_port == "" || num_scenes == 0 || num_arduinos == 0)
		ofLogWarning("XML Settings") << "Missing general properties";
	else {
		ofLogNotice("MIDI Port Name") << midi_port;
		ofLogNotice("DMX Port Name") << dmx_port;
		ofLogNotice("Number of scenes") << num_scenes;
	}

	//	Load individual scene settings
	for (int i = 0; i < num_scenes; ++i)
	{
		scenes.push_back(new Scene());
		scenes.at(i)->name = scene_settings.getValue("scene:name", "", i);
		scenes.at(i)->length = scene_settings.getValue("scene:length", 0, i);
		scenes.at(i)->ard_port = scene_settings.getValue("scene:arduino_port", "", i);
		scenes.at(i)->num_rooms = scene_settings.getValue("scene:num_rooms", 0, i);
		scenes.at(i)->rooms.assign(scenes.at(i)->num_rooms, Room());

		//	Add to scene map (so we can reference scenes by name)
		scene_map.insert(std::pair<string, Scene*>(scenes.at(i)->name, scenes.at(i)));

		//	Load individual room settings
		scene_settings.pushTag("scene", i);
		
		for (int j = 0; j < scenes.at(i)->num_rooms; ++j)
		{
			scene_settings.pushTag("room", j);
			scenes.at(i)->rooms.at(j).name = scene_settings.getValue("name", "");
			scenes.at(i)->rooms.at(j).midi_channel = scene_settings.getValue("midi_channel", 0);
			scenes.at(i)->rooms.at(j).dmx_channel = scene_settings.getValue("dmx_channel", 0);
			scenes.at(i)->rooms.at(j).dmx_init_level = scene_settings.getValue("dmx_init_level", 0);
			scene_settings.popTag();
		}

		scene_settings.popTag();

		//	Validate scene settings
		if (scenes.at(i)->name == "" || scenes.at(i)->length == 0 || scenes.at(i)->num_rooms == 0)
			ofLogWarning("XML Settings") << "Missing properties for scene " << i;
	}

	ofLogNotice("XML scene settings") << "SUCCESS!";
}

//--------------------------------------------------------------
void ofApp::setupMIDI()
{
	//	Print the available output ports to the console
	//	midiOut.listPorts();

	//	Force port to close down in case we need to reconnect
	if (midiOut.isOpen())
		midiOut.closePort();

	//	Connect
	bool b_MIDI_Connect = midiOut.openPort(midi_port);

	if (!b_MIDI_Connect)
		ofLogWarning("MIDI") << "Couldn't connect to MIDI port " << midi_port;
	else
		ofLogNotice("MIDI") << "connected to port " << midi_port << " SUCCESS!";

	//	Give each scene a pointer to this MIDI out object
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->midiOut = &midiOut;
	}
}

//--------------------------------------------------------------
void ofApp::setupDMX()
{
	//	Force port to close down in case we need to reconnect
	if (dmx.isConnected())
	{
		dmx.clear();
		dmx.update(true);
		dmx.disconnect();
	}

	//	Connect
	bool b_DMX_Connect = dmx.connect("COM5");

	if (!b_DMX_Connect)
		ofLogWarning("DMX") << "Couldn't connect to DMX interface through port " << dmx_port;
	else
		ofLogNotice("DMX") << "connected to DMX interface through port " << dmx_port << " SUCCESS!";

	//	Give each scene a pointer to this DMX object
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->dmx = &dmx;
	}
}

//--------------------------------------------------------------
void ofApp::initArduinos()
{
	//	Connect the arduino
	for (int i = 0; i < scenes.size(); ++i)
	{
		int ard_count = ards.size();

		if (scenes.at(i)->ard_port != "")
		{
			ards.push_back(new ofArduino);
			scenes.at(i)->ard = ards.at(ard_count);
			scenes.at(i)->ard->connect(scenes.at(i)->ard_port, 9600);
			scenes.at(i)->ard->sendFirmwareVersionRequest();
			ofAddListener(scenes.at(i)->ard->EInitialized, scenes.at(i), &Scene::setupArduino);
		}
	}
}

//--------------------------------------------------------------
void ofApp::updateArduinos()
{
	for (int i = 0; i < ards.size(); ++i)
	{
		ards.at(i)->update();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//	MIDI to Ableton Test
	switch (key)
	{
	case '1' :
		midiOut.sendNoteOn(1, NOTE, VELOCITY);
		break;
	case '2':
		midiOut.sendNoteOn(2, NOTE, VELOCITY);
		break;
	case '3':
		midiOut.sendNoteOn(3, NOTE, VELOCITY);
		break;
	case '4':
		midiOut.sendNoteOn(4, NOTE, VELOCITY);
		break;
	case '5':
		midiOut.sendNoteOn(5, NOTE, VELOCITY);
		break;
	case '6':
		midiOut.sendNoteOn(6, NOTE, VELOCITY);
		break;
	case 'm':
		setupMIDI();
		break;
	case 'u':
		scene_map.at("underwater")->launchScene();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

/*
void ofApp::setupArduino(const int & version)
{
//	Remove listener because we don't need it anymore
ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);

//	It is now safe to send commands to the Arduino
bSetupArd = true;

//	Print firmware name and version to the console
ofLogNotice() << ard.getFirmwareName();
ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

//	Set pin D2 as digital input
ard.sendDigitalPinMode(2, ARD_INPUT);

//	Listen for changes on the digital and analog pins
ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

void ofApp::digitalPinChanged(const int & pin_num)
{
}

void ofApp::analogPinChanged(const int & pin_num)
{
}
*/