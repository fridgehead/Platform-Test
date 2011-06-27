#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ready = false;
	
	gameMap = new GameMap(&spriteManager,100,20);
	gameMap->loadFromFile("doesntmatter");
	
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
	
	testPlayer = new Player(gameMap->spawnPos, testSprite);
	testPlayer->speed = ofPoint(0,0);
	//testSprite->boundingBoxSize = ofPoint(66,108);
	ready = true;
	
	watermark.loadImage("watermark.png");
	backgroundImage.allocate(64,64,OF_IMAGE_COLOR);
	unsigned char * temp = new unsigned char[64*64*3];
	for(int x = 0; x < 64; x++){
		for(int y = 0; y < 64; y++){		
			int basePos = (x + y * 64) * 3 ;
			temp[basePos] = 0;
			temp[basePos + 1] = 0;
			temp[basePos + 2] = y * 4;
			
		}
	}
	backgroundImage.setFromPixels(temp, 64, 64, OF_IMAGE_COLOR, true);
	delete[] temp;
}

//--------------------------------------------------------------
void testApp::update(){
	if(ready){
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
	if (cx <32){
		cx = 32;
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
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(53,171,254);
	//draw bg
	backgroundImage.draw(0,0,1024,768);
	
	gameMap->drawMap(camera);
	//screen space drawing
	ofPoint spriteScreenPos = camera->worldToScreen(ofPoint(200, 200));
	if(spriteScreenPos.x != -1 && spriteScreenPos.y != -1){
	//	sprite->draw(spriteScreenPos.x, spriteScreenPos.y,4);
	}
	//world space drawing
	spriteScreenPos = camera->worldToScreen(ofPoint(testPlayer->worldPos.x, testPlayer->worldPos.y));
	if(spriteScreenPos.x != -1 && spriteScreenPos.y != -1){
		testSprite->draw(spriteScreenPos.x, spriteScreenPos.y,0);
		ofNoFill();
		ofRect(spriteScreenPos.x + testPlayer->getBoundingBox().x, spriteScreenPos.y + testPlayer->getBoundingBox().y , testPlayer->getBoundingBox().width, testPlayer->getBoundingBox().height);
	}

	watermark.draw(700, 700);

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
				testSprite->setAnimation(ANIM_JUMP);
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

