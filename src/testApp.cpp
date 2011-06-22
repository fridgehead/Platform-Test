#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	sprite = new GameSprite(&spriteManager);
	sprite->pos = ofPoint(20,20);
	
}

//--------------------------------------------------------------
void testApp::update(){
	sprite->pos = ofPoint(mouseX,mouseY);
	sprite->think();
}

//--------------------------------------------------------------
void testApp::draw(){
	sprite->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

