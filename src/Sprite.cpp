/*
 *  Sprite.cpp
 *  Platform
 *
 *  Created by Tom Wyatt on 22/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sprite.h"

GameSprite::GameSprite(SpriteManager* spriteman){
	pos = ofPoint(10,10);
	currentFrame = 0;
	lastFrameTime = 0;
	
	spriteman->loadImageFile("ass.png");
}

void GameSprite::draw(){
	ofRect(pos.x, pos.y, 10,10);
}


void GameSprite::think(){
	if(lastFrameTime + 1000  < ofGetElapsedTimeMillis() ){
		lastFrameTime = ofGetElapsedTimeMillis();
		currentFrame ++;
		currentFrame %= 5;
	}
	
	
	
}



