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
	spriteMan = spriteman;
	mirror = false;
	
}

void GameSprite::loadData(string tag){
	spriteDataIndex = spriteMan->loadDataFile(tag);
	currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
	cout << spriteDataIndex << endl;
	currentImage.allocate(currentImageData->dimensions.x, currentImageData->dimensions.y, OF_IMAGE_COLOR_ALPHA);
	currentImage.setAnchorPoint(currentImageData->dimensions.x / 2 , currentImageData->dimensions.y /2 );
	setAnimation(ANIM_WALK);
	
}
	
void GameSprite::setAnimation(AnimationName anim){
	
	//look up anim in spritemanager
	currentImageData = &(spriteMan->spriteData[spriteDataIndex]);
	vector<Animation>::iterator it;
	for( it = currentImageData->animations.begin(); it != currentImageData->animations.end(); it++){
		if(it->index == (int)anim){
			cout << "found animation id: " << anim << endl;
			currentAnimation = *it;
			currentFrame = 0;
			
			
			
			
		}
	}
	
}

void GameSprite::draw(){
	ofRect(pos.x, pos.y, 10,10);
	
	currentImage.draw(pos.x,pos.y, currentImageData->dimensions.x * 4, currentImageData->dimensions.y * 4);
	
}



void GameSprite::think(){
	if(lastFrameTime + 60  < ofGetElapsedTimeMillis() ){
		lastFrameTime = ofGetElapsedTimeMillis();
		currentFrame ++;
		currentFrame %= currentAnimation.numFrames ;
		//cout << currentFrame << endl;
		//get the subimage of the sprite image
		int width = currentImageData->dimensions.x;
		int height = currentImageData->dimensions.y;
		unsigned char * newPix = new unsigned char [ width * height * 4];
		unsigned char * pix = currentImageData->image.getPixels();

		int srcX = currentFrame * width;
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
		
			
			
		delete[] newPix;
		
	}
	
	
	
}



