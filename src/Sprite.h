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
enum AnimationName {
	ANIM_WALK = 0,
	ANIM_STOP = 1,
	ANIM_DYING = 2,
	ANIM_DEAD = 3,
	ANIM_INJURED = 4,
	ANIM_JUMP = 5
};




class GameSprite {
	
public:
	GameSprite (SpriteManager* spriteMan);
	~GameSprite();
	void think();
	void draw();
	void loadData(string tag);
	void setAnimation(AnimationName anim);
	
	ofPoint pos;
	bool mirror;
	
	
private:
		
	int currentFrame;
	Animation currentAnimation;
	ImageData* currentImageData;

	ofImage currentImage;
	long lastFrameTime;
	SpriteManager* spriteMan;
	int spriteDataIndex;
	
	
	
};


#endif