/*
 *  Sprite.h
 *  Platform
 *
 *  Created by Tom Wyatt on 22/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _SPRITE
#define _SPRITE

#include "ofMain.h"
#include "SpriteManager.h"

class GameSprite {
	
public:
	GameSprite (SpriteManager* spriteMan);
	~GameSprite();
	void think();
	void draw();
	
	ofPoint pos;
	
private:
	int currentFrame;
	long lastFrameTime;
	
	
};


#endif