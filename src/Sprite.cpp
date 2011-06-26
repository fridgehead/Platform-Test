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
	lastFrameTime = ofGetElapsedTimeMillis();
	spriteMan = spriteman;
	mirror = false;
	empty = false;
	lastFrame = -1;
	
}

GameSprite::~GameSprite(){
}

void GameSprite::loadData(string tag){
	//cout << "Loading data for: " << tag <<endl;
	spriteDataIndex = spriteMan->loadDataFile(tag);
	//cout << ".... index is " << spriteDataIndex << endl;
	currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
	//cout << "!!!!tag: " << currentImageData->tag << endl;
	currentImage.allocate(currentImageData->dimensions.x, currentImageData->dimensions.y, OF_IMAGE_COLOR_ALPHA);
	//currentImage.setAnchorPoint(currentImageData->dimensions.x / 2 , currentImageData->dimensions.y /2 );
	//setAnimation(ANIM_WALK);
	
}

void GameSprite::setAnimation(int anim){
	
	//look up anim in spritemanager
	if(spriteDataIndex > spriteMan->spriteData.size()){
		cout << "FUCK" << endl;
	}
	currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
	//cout << "setting animation for " << currentImageData->tag << endl;
	vector<Animation>::iterator it;
	bool ok;
	ok = false;
	for( it = currentImageData->animations.begin(); it != currentImageData->animations.end(); it++){
		if(it->index == anim){
			//cout << "Set animation id: " << anim << endl;
			currentAnimation.index = it->index;
			currentAnimation.numFrames = it->numFrames;
			currentAnimation.spriteRow = it->spriteRow;
			currentAnimation.animSpeed = it->animSpeed;
			//cout << "got animation index: " << currentAnimation.numFrames << endl;
			currentFrame = 0;
			lastFrameTime = ofGetElapsedTimeMillis() - it->animSpeed - 10;
			ok = true;
			
			
			
			setCurrentFrame(currentFrame);
			if(currentAnimation.animSpeed > 0){
				think();
			}
			
			
		}
	}
	if(!ok){
		cout << "setting animation that doesnt exist!! - " << anim << endl;
	}
	
}

void GameSprite::draw(int x, int y, int scale){
	//ofRect(pos.x, pos.y, 10,10);
	currentImageData = &(spriteMan->spriteData[spriteDataIndex]);

	
	currentImage.draw(x,y, currentImageData->dimensions.x * scale  , currentImageData->dimensions.y * scale);
//	currentImageData->image.draw(x,y, 32  , 32);
}

void GameSprite::setCurrentFrame(int frame){
	if (frame < currentAnimation.numFrames && currentFrame != lastFrame){
		
		currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
		
		int width = currentImageData->dimensions.x;
		int height = currentImageData->dimensions.y;
		unsigned char * newPix = new unsigned char [ width * height * 4];
		unsigned char * pix = currentImageData->image.getPixels();
		
		int srcX = frame * width;
		int srcY = currentAnimation.spriteRow * height;
		int ct = 0;
		for(int x = 0; x < width; x++){
			for(int y = 0; y < height; y++){
				int subPos = 0;
				if(mirror){
					subPos = ((width - x) + y * width) * 4;
				} else {
					subPos = (x + y * width) * 4;
				}
				int mainPos = ((srcX + x) + (srcY + y) * currentImageData->image.width) * 4;
				newPix[subPos] = pix[mainPos];
				newPix[subPos + 1] = pix[mainPos + 1];
				newPix[subPos + 2] = pix[mainPos + 2];
				newPix[subPos + 3] = pix[mainPos + 3];			
			}
		}
		currentImage.setFromPixels(newPix, width,height, OF_IMAGE_COLOR_ALPHA, true);
		lastFrame = currentFrame;
		
		
		delete[] newPix;
	}
}



void GameSprite::think(){
	if(currentAnimation.animSpeed > 0){
		
		
		
		
		if(lastFrameTime + currentAnimation.animSpeed  < ofGetElapsedTimeMillis() ){
			//currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
			//cout << "think : " << currentImageData->tag << endl;
			lastFrameTime = ofGetElapsedTimeMillis();
			lastFrame = currentFrame;
			currentFrame ++;
			currentFrame %= currentAnimation.numFrames ;
			//cout << currentFrame << endl;
			//get the subimage of the sprite image
			setCurrentFrame(currentFrame);
			
		}
	} else {
		setCurrentFrame(0);
	}
	
	
	
}



