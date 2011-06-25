#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	
	gameMap = new GameMap(&spriteManager,100,20);
	
	
	sprite = new GameSprite(&spriteManager);
	sprite->pos = ofPoint(20,20);
	sprite->loadData("test");
	cout << "setting" << endl;
	sprite->setAnimation(ANIM_WALK);
	
	testSprite = new GameSprite(&spriteManager);
	testSprite->pos = ofPoint(200,200);
	testSprite->loadData("ass");
	testSprite->setAnimation(ANIM_STOP);
	testSprite->mirror = true;
	
	camera = new Camera(1024, 768);
	
	playerX = 200;
	playerY = 200;
	dir = 0;
	ofSetFrameRate(30);
	
	testPlayer = new Player(ofPoint(150,250), testSprite);
	testPlayer->speed = ofPoint(0,0);
	testPlayer->boundingBoxSize = ofPoint(66,108);
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	testPlayer->speed.x = dir * 10;
	testPlayer->think();

	gameMap->checkCollision((GameObject*)testPlayer);

	
	
	sprite->pos = ofPoint(mouseX,mouseY);
	sprite->think();
	playerX += dir * 3;
	//testSprite->pos = ofPoint(playerX, 200);
	//testSprite->think();
	//testPlayer->worldPos = ofPoint(playerX, playerY);
	
	
	int cx = testPlayer->worldPos.x - 512;
	if (cx <0){
		cx = 0;
	} else if (cx > gameMap->mapWidth * 64){
		cx = gameMap->mapWidth * 64;
	}
	int cy = testPlayer->worldPos.y - 384;
	if (cy < 0){
		cy = 0;
	} else if (cy > gameMap->mapWidth * 64){
		cy = gameMap->mapWidth * 64;
	}
	camera->worldPosition = ofPoint(cx, cy);
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(53,171,254);
	//draw bg
	
	gameMap->drawMap(camera);
	//screen space drawing
	ofPoint spriteScreenPos = camera->worldToScreen(ofPoint(200, 200));
	if(spriteScreenPos.x != -1 && spriteScreenPos.y != -1){
	//	sprite->draw(spriteScreenPos.x, spriteScreenPos.y,4);
	}
	//world space drawing
	spriteScreenPos = camera->worldToScreen(ofPoint(testPlayer->worldPos.x, testPlayer->worldPos.y));
	if(spriteScreenPos.x != -1 && spriteScreenPos.y != -1){
		testSprite->draw(spriteScreenPos.x, spriteScreenPos.y,2);
		ofNoFill();
		ofRect(spriteScreenPos.x, spriteScreenPos.y, testPlayer->boundingBoxSize.x, testPlayer->boundingBoxSize.y);
	}
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
		case 357:
			//playerY -= 10;
			break;
		case 359:
			//playerY += 10;
			break;
		case 32:
			if(testPlayer->isJumping == false){
				testPlayer->speed.y = -30;
				testPlayer->isJumping = true;
				testPlayer->isOnGround = false;
				cout << "jump" << endl;
			}
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

	sprite->setAnimation(ANIM_WALK);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

