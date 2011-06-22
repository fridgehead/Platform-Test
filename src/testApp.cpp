#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	sprite = new GameSprite(&spriteManager);
	sprite->pos = ofPoint(20,20);
	sprite->loadData("test");
	
	sprite->setAnimation(ANIM_WALK);
	
	testSprite = new GameSprite(&spriteManager);
	testSprite->pos = ofPoint(200,200);
	testSprite->loadData("ass");
	testSprite->mirror = true;
	
	playerX = 200;
	dir = 0;
	ofSetFrameRate(30);
	
}

//--------------------------------------------------------------
void testApp::update(){
	sprite->pos = ofPoint(mouseX,mouseY);
	sprite->think();
	playerX += dir * 10;
	testSprite->pos = ofPoint(playerX, 200);
	testSprite->think();
}

//--------------------------------------------------------------
void testApp::draw(){
	sprite->draw();
	testSprite->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	cout << key << endl;
	switch(key){
		case 356: //left
			if(dir != -1){
				testSprite->setAnimation(ANIM_WALK);
				testSprite->mirror = true;
			}
			dir = -1;
			
			break;
		case 358: //right
			if(dir != 1){
				testSprite->setAnimation(ANIM_WALK);
				testSprite->mirror = false;
			}
			dir = 1;
			


			break;
	}


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(dir != 0){
		testSprite->setAnimation(ANIM_STOP);
	}
	dir = 0;
	
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	sprite->setAnimation(ANIM_JUMP);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

