#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	OF Settings
	ofBackground(0);
	ofSetFrameRate(30);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);

	//	Read in XML settings
	loadSceneSettings();
	//	Connect to MIDI port
	setupMIDI();
	//	Connect to DMX interface
	setupDMX();
	//	GUI setup
	setupGUI();
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

	drawGUI();
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
	udp_command = scene_settings.getValue("general:udp_command", "");
	udp_ip = scene_settings.getValue("general:udp_ip", "");
	udp_port = scene_settings.getValue("general:udp_port", 0);

	if (midi_port == "" || dmx_port == "" || num_scenes == 0 || num_arduinos == 0 || udp_command == "" || udp_ip == "" || udp_port == 0)
		ofLogWarning("XML Settings") << "Missing general properties";
	else {
		ofLogNotice("MIDI Port Name") << midi_port;
		ofLogNotice("DMX Port Name") << dmx_port;
		ofLogNotice("Number of scenes") << num_scenes;
		ofLogNotice("UDP Command") << udp_command;
		ofLogNotice("UDP IP Address") << udp_ip;
		ofLogNotice("UDP Port") << udp_port;
	}

	//	Load individual scene settings
	for (int i = 0; i < num_scenes; ++i)
	{
		scenes.push_back(new Scene());
		scenes.at(i)->name = scene_settings.getValue("scene:name", "", i);
		scenes.at(i)->length = scene_settings.getValue("scene:length", 0, i);
		scenes.at(i)->ard_port = scene_settings.getValue("scene:arduino_port", "", i);
		scenes.at(i)->num_rooms = scene_settings.getValue("scene:num_rooms", 0, i);

		//	Add UDP messaging settings to Lethal Scene
		if (scenes.at(i)->name == "injection")
		{
			scenes.at(i)->udp_command = udp_command;
			scenes.at(i)->udp_ip = udp_ip;
			scenes.at(i)->udp_port = udp_port;
		}

		//	Add to scene map (so we can reference scenes by name)
		scene_map.insert(std::pair<string, Scene*>(scenes.at(i)->name, scenes.at(i)));

		//	Load individual room settings
		scene_settings.pushTag("scene", i);
		
		for (int j = 0; j < scenes.at(i)->num_rooms; ++j)
		{
			scene_settings.pushTag("room", j);
			scenes.at(i)->rooms.push_back(new Room);
			scenes.at(i)->rooms.at(j)->name = scene_settings.getValue("name", "");
			scenes.at(i)->rooms.at(j)->midi_channel = scene_settings.getValue("midi_channel", 0);
			scenes.at(i)->room_map.insert(pair<string, Room*>(scenes.at(i)->rooms.at(j)->name, scenes.at(i)->rooms.at(j)));

			int num_dmx = scene_settings.getValue("num_dmx", 0);
			for (int k = 0; k < num_dmx; ++k)
			{
				int dmx_channel = scene_settings.getValue("dmx_channel", 0, k);
				int init_level = scene_settings.getValue("dmx_init_level", 0, k);
				scenes.at(i)->rooms.at(j)->dmx_map.insert(pair<int, int>(dmx_channel, init_level));
				scenes.at(i)->rooms.at(j)->dmx_channels.push_back(dmx_channel);
			}

			//scenes.at(i)->rooms.at(j).dmx_channel = scene_settings.getValue("dmx_channel", 0);
			//scenes.at(i)->rooms.at(j).dmx_init_level = scene_settings.getValue("dmx_init_level", 0);
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
	bool b_DMX_Connect = dmx.connect(dmx_port);

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
void ofApp::setupGUI(){

	//	Add listeners
	for (int i = 0; i < 16; ++i)
	{
		ofxToggle toggle;
		midi_toggles.push_back(toggle);
	}

	midi_toggles.at( 0).addListener(this, &ofApp::toggled_01);
	midi_toggles.at( 1).addListener(this, &ofApp::toggled_02);
	midi_toggles.at( 2).addListener(this, &ofApp::toggled_03);
	midi_toggles.at( 3).addListener(this, &ofApp::toggled_04);
	midi_toggles.at( 4).addListener(this, &ofApp::toggled_05);
	midi_toggles.at( 5).addListener(this, &ofApp::toggled_06);
	midi_toggles.at( 6).addListener(this, &ofApp::toggled_07);
	midi_toggles.at( 7).addListener(this, &ofApp::toggled_08);
	midi_toggles.at( 8).addListener(this, &ofApp::toggled_09);
	midi_toggles.at( 9).addListener(this, &ofApp::toggled_10);
	midi_toggles.at(10).addListener(this, &ofApp::toggled_11);
	midi_toggles.at(11).addListener(this, &ofApp::toggled_12);
	midi_toggles.at(12).addListener(this, &ofApp::toggled_13);
	midi_toggles.at(13).addListener(this, &ofApp::toggled_14);
	midi_toggles.at(14).addListener(this, &ofApp::toggled_15);
	midi_toggles.at(15).addListener(this, &ofApp::toggled_16);

	//	Setup panel
	midi_panel.setup("", "settings.xml", 522, 20);
	midi_panel.setName("MIDI Player");
	for (int i = 0; i < 16; ++i)
	{
		midi_panel.add(midi_toggles.at(i).setup("Channel " + ofToString(i+1), false));
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

void ofApp::hardStop()
{
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->eStop();
	}
}

//--------------------------------------------------------------
void ofApp::restart()
{
	for (int i = 0; i < scenes.size(); ++i)
	{
		scenes.at(i)->restart();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//	MIDI to Ableton Test
	switch (key)
	{
	case 'E':
		hardStop();
		break;
	case 'i':
		scene_map.at("injection")->launchScene();
		break;
	case 'I':
		scene_map.at("injection")->endScene();
		break;
	case 'M':
		setupMIDI();
		break;
	case 'R':
		restart();
		break;
	case 's':
		scene_map.at("separation")->launchScene();
		break;
	case 'S':
		scene_map.at("separation")->endScene();
		break;
	case 'u':
		scene_map.at("underwater")->launchScene();
		break;
	case 'U':
		scene_map.at("underwater")->endScene();
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
void ofApp::sendMidiOn(const int& channel){
	midiOut.sendNoteOn(channel, NOTE, VELOCITY);
}

//--------------------------------------------------------------
void ofApp::sendMidiOff(const int& channel){
	midiOut.sendNoteOff(channel, NOTE, 0);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::drawGUI() {

	//	Draw scene statuses
	//	***************************************
	//	Separation rooms
	if (scene_map.at("separation")->b_Running)
	{
		ofSetColor(146, 45, 80);
		ofDrawRectangle(20, 20, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Separation rooms running...", 30, 45);
		ofDrawBitmapString(int(scene_map.at("separation")->length - scene_map.at("separation")->run_time), 456, 45);
	}
	else
	{
		ofSetColor(4, 80, 98);
		ofDrawRectangle(20, 20, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Separation rooms idle...", 30, 45);
	}
	ofSetColor(255);
	ofDrawBitmapString("It Rooms", 30, 80);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(1));
	ofDrawRectangle(30, 90, 40, 40);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(2));
	ofDrawRectangle(80, 90, 40, 40);

	ofSetColor(255);
	ofDrawBitmapString("Shining Rooms", 180, 80);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(3));
	ofDrawRectangle(180, 90, 40, 40);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(3));
	ofDrawRectangle(230, 90, 40, 40);

	ofSetColor(255);
	ofDrawBitmapString("Shawshank Rooms", 330, 80);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(4));
	ofDrawRectangle(330, 90, 40, 40);
	ofSetColor(scene_map.at("separation")->dmx->getLevel(4));
	ofDrawRectangle(380, 90, 40, 40);

	//	Underwater room
	if (scene_map.at("underwater")->b_Running)
	{
		ofSetColor(146, 45, 80);
		ofDrawRectangle(20, 150, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Underwater room running...", 30, 175);
		ofDrawBitmapString(int(scene_map.at("underwater")->length - scene_map.at("underwater")->run_time), 456, 175);

	}
	else
	{
		ofSetColor(4, 80, 98);
		ofDrawRectangle(20, 150, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Underwater room idle...", 30, 175);
	}
	ofSetColor(255);
	ofDrawBitmapString("Headlight", 30, 210);
	scene_map.at("underwater")->ard->getDigital(2) == 1 ?
		ofSetColor(255) :
		ofSetColor(0);
	ofDrawRectangle(30, 220, 40, 40);

	ofSetColor(255);
	ofDrawBitmapString("Spotlight", 180, 210);
	ofSetColor(scene_map.at("underwater")->dmx->getLevel(4));
	ofDrawRectangle(180, 220, 40, 40);


	//	Injection room
	if (scene_map.at("injection")->b_Running)
	{
		ofSetColor(146, 45, 80);
		ofDrawRectangle(20, 280, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Injection room running...", 30, 305);
		ofDrawBitmapString(int(scene_map.at("injection")->length - scene_map.at("injection")->run_time), 456, 305);
	}
	else
	{
		ofSetColor(4, 80, 98);
		ofDrawRectangle(20, 280, 472, 40);
		ofSetColor(255);
		ofDrawBitmapString("Injection room idle...", 30, 305);
	}
	ofSetColor(255);
	ofDrawBitmapString("Alarm light", 30, 340);
	scene_map.at("injection")->ard->getDigital(2) == 1 ?
		ofSetColor(255, 0, 0) :
		ofSetColor(0);
	ofDrawRectangle(30, 350, 40, 40);

	//	Panel
	midi_panel.draw();
}

//--------------------------------------------------------------
void ofApp::toggled_01(bool& on) {
	if (on)
	{
		sendMidiOn(1);
	}
	else
	{
		sendMidiOff(1);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_02(bool& on) {
	if (on)
	{
		sendMidiOn(2);
	}
	else
	{
		sendMidiOff(2);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_03(bool& on) {
	if (on)
	{
		sendMidiOn(3);
	}
	else
	{
		sendMidiOff(3);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_04(bool& on) {
	if (on)
	{
		sendMidiOn(4);
	}
	else
	{
		sendMidiOff(4);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_05(bool& on) {
	if (on)
	{
		sendMidiOn(5);
	}
	else
	{
		sendMidiOff(5);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_06(bool& on) {
	if (on)
	{
		sendMidiOn(6);
	}
	else
	{
		sendMidiOff(6);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_07(bool& on) {
	if (on)
	{
		sendMidiOn(7);
	}
	else
	{
		sendMidiOff(7);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_08(bool& on) {
	if (on)
	{
		sendMidiOn(8);
	}
	else
	{
		sendMidiOff(8);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_09(bool& on) {
	if (on)
	{
		sendMidiOn(9);
	}
	else
	{
		sendMidiOff(9);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_10(bool& on) {
	if (on)
	{
		sendMidiOn(10);
	}
	else
	{
		sendMidiOff(10);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_11(bool& on) {
	if (on)
	{
		sendMidiOn(11);
	}
	else
	{
		sendMidiOff(11);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_12(bool& on) {
	if (on)
	{
		sendMidiOn(12);
	}
	else
	{
		sendMidiOff(12);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_13(bool& on) {
	if (on)
	{
		sendMidiOn(13);
	}
	else
	{
		sendMidiOff(13);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_14(bool& on) {
	if (on)
	{
		sendMidiOn(14);
	}
	else
	{
		sendMidiOff(14);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_15(bool& on) {
	if (on)
	{
		sendMidiOn(15);
	}
	else
	{
		sendMidiOff(15);
	}
}

//--------------------------------------------------------------
void ofApp::toggled_16(bool& on) {
	if (on)
	{
		sendMidiOn(16);
	}
	else
	{
		sendMidiOff(16);
	}
}