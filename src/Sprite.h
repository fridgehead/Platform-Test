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
	ANIM_JUMP = 5,
	TILE_TOP = 6,
	TILE_BOTTOM = 7,
	TILE_TOP_RIGHT = 8,
	TILE_TOP_LEFT = 9,
	TILE_BOTTOM_LEFT = 10,
	TILE_BOTTOM_RIGHT = 11,
	TILE_MIDDLE = 12,
	
	
};




class GameSprite {
	
public:
	GameSprite (SpriteManager* spriteMan);
	GameSprite();
	~GameSprite();
	void think();
	void draw(int x, int y, int scale);
	void loadData(string tag);
	void setAnimation(AnimationName anim);
	
	ofPoint pos;
	bool mirror;
	bool empty;
	SpriteManager* spriteMan;
	
private:
		
	int currentFrame;
	Animation currentAnimation;
	ImageData* currentImageData;

	ofImage currentImage;
	long lastFrameTime;
	int spriteDataIndex;
	
	
	
};


#endif