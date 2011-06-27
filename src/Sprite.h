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
	TILE_MIDDLE = 6,
	TILE_TOP = 7,
	TILE_BOTTOM = 8,
	TILE_TOP_LEFT = 9,
	TILE_TOP_RIGHT = 10,
	TILE_BOTTOM_RIGHT = 11,
	TILE_BOTTOM_LEFT = 12	
};




class GameSprite {
	
public:
	GameSprite (SpriteManager* spriteMan);
	GameSprite();
	~GameSprite();
	void think();
	void draw(int x, int y, int scale);
	void loadData(string tag);
	void setAnimation(int anim);
	
	ofPoint pos;
	bool mirror;
	bool empty;
	SpriteManager* spriteMan;
	bool collided;
	void setCurrentFrame(int frame); //uses current anim;
	Animation currentAnimation;
	int currentFrame, lastFrame;
	float scale;
	ofRectangle boundingBox;

private:
	
	
	ImageData* currentImageData;

	ofImage currentImage;
	long lastFrameTime;
	int spriteDataIndex;
	
	
	
	
};


#endif