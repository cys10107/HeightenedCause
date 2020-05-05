#include "ofApp.h"
int tempCounter = 0;
//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
//int counter = 0;
void ofApp::update(){
	/*counter += 1;
	if (counter == 3)
	{*/
		//counter = 0;
		this->stage.movementUpdate();
		this->stage.update();
		this->stage.CamUpdate();
		if (this->stage.winTest() && this->CurrentStage + 1 <= STAGE_NUMBERS)
		{
			//this->CurrentStage++;
			this->stage = Scene(this->CurrentStage);
		}
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (this->stage.loaded)
	{
		this->stage.display();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case OF_KEY_RIGHT:
	case 'd':
		stage.d_pressed = true;
		break;
	case OF_KEY_LEFT:
	case 'a':
		stage.a_pressed = true;
		break;
	case OF_KEY_DOWN:
	case 's':
		stage.s_pressed = true;
		break;
	case OF_KEY_UP:
	case 'w':
		stage.w_pressed = true;
		break;
		/*
	case OF_KEY_UP:
		stage.up_pressed = true;
		break;
	case OF_KEY_DOWN:
		stage.down_pressed = true;
		break;
	case 'o':
		stage.writeCurrentStageToFile();
		break;*/
	case 'l':
		stage.reloadStage();
		break;
	case '1':
		stage.loadStage(1);
		break;
	case '2':
		stage.loadStage(2);
		break;
	case 'k':
		stage.dead();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case OF_KEY_RIGHT:
	case 'd':
		stage.d_pressed = false;
		break;
	case OF_KEY_LEFT:
	case 'a':
		stage.a_pressed = false;
		break;
	case OF_KEY_DOWN:
	case 's':
		stage.s_pressed = false;
		break;
	case OF_KEY_UP:
	case 'w':
		stage.w_pressed = false;
		break;
		/*
	case OF_KEY_UP:
		stage.up_pressed = false;
		break;
	case OF_KEY_DOWN:
		stage.down_pressed = false;
		break;*/
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button) {
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
