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
	testSprite->mirror = true;
	
	camera = new Camera(1024, 768);
	
	playerX = 200;
	playerY = 200;
	dir = 0;
	ofSetFrameRate(30);
	
}

//--------------------------------------------------------------
void testApp::update(){
	sprite->pos = ofPoint(mouseX,mouseY);
	sprite->think();
	playerX += dir * 10;
	//testSprite->pos = ofPoint(playerX, 200);
	testSprite->think();
	
	
	int cx = playerX - 512;
	if (cx <0){
		cx = 0;
	} else if (cx > gameMap->mapWidth * 64){
		cx = gameMap->mapWidth * 64;
	}
	int cy = playerY - 384;
	if (cy < 0){
		cy = 0;
	} else if (cy > gameMap->mapWidth * 64){
		cy = gameMap->mapWidth * 64;
	}
	camera->worldPosition = ofPoint(cx, cy);
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//draw bg
	//GameSprite* mapArea;
	//gameMap->getMapArea(ofRectangle(0, 0, 10, 10), mapArea);
	
	/*for(int x = 0; x < 10; x ++){
		for(int y = 0; y < 10; y++){
			GameSprite* b = &mapArea[x + y * 10];
			if(b != 0){
				//b->think();
				//b->pos = ofPoint(x * 32, y * 32);
				//b->draw();
			}
		}
	}*/
	//delete[] mapArea;
	gameMap->drawMap(camera);
	
	
	
	sprite->draw(200,200,4);
	
	ofPoint spriteScreenPos = camera->worldToScreen(ofPoint(playerX, playerY));
	if(spriteScreenPos.x != -1 && spriteScreenPos.y != -1){
		testSprite->draw(spriteScreenPos.x, spriteScreenPos.y,4);
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
			playerY -= 10;
			break;
		case 359:
			playerY += 10;
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

