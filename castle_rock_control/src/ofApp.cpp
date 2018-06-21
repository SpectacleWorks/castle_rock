#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	OF Settings
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);

	//	Read in XML settings
	loadMidiSettings();

	//	MIDI setup
	//	Print the available output ports to the console
	//	midiOut.listPorts();
	//	Connect
	bool b_MIDI_Connect = midiOut.openPort(midi_port);

	if (!b_MIDI_Connect)
		ofLogWarning("MIDI") << "Couldn't connect to MIDI port " << midi_port;
	else
		ofLogNotice("MIDI") << "connected to port " << midi_port << " SUCCESS!";
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit() {

	// clean up
	midiOut.closePort();
}

void ofApp::loadMidiSettings()
{
	//	Load general settings
	xml_midi_settings.loadFile("midi_settings.xml");
	midi_port = xml_midi_settings.getValue("general:port_name", "");
	num_channels = xml_midi_settings.getValue("general:num_channels", 0);

	if (midi_port == "" || num_channels == 0)
		ofLogWarning("XML MIDI Settings") << "Couldn't locate port name or number of channels";
	else {
		ofLogNotice("MIDI Port Name") << midi_port;
		ofLogNotice("MIDI channels") << num_channels;
	}

	for (int i = 0; i < num_channels; ++i)
	{
		//	Load settings for each channel
		string tag = "channel" + ofToString(i+1);
		string room = xml_midi_settings.getValue(tag + ":room", "");
		int channel = xml_midi_settings.getValue(tag + ":midi_channel", 0);

		//	Error hanndling
		if (room == "" || channel == -1)
		{
			ofLogWarning("XML MIDI settings") << "Couldn't locate room or MIDI channel";
		}

		//	Add it to the map
		midi_settings.insert(pair<string, int>(room, channel));

		ofLogNotice("MIDI route") << room << " sent to MIDI channel " << channel;
	}

	ofLogNotice("XML MIDI settings") << "SUCCESS!";
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
