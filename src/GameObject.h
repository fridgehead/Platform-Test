/*
 *  GameObject.h
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAMEOBJECT
#define GAMEOBJECT
#include "ofMain.h"
#include "Sprite.h"


class GameObject {
public:
	GameObject(ofPoint worldPosition, GameSprite* spt);
	~GameObject();
	virtual void think() = 0;
	ofRectangle getBoundingBox();
	
	ofPoint worldPos;			//top left of sprite for now
	ofPoint boundingBoxSize;	//worldPos + bb size defines BB
	ofPoint speed;
	bool isMoving, isJumping, isOnGround;
	
protected:
	GameSprite* sprite;
};



class Player : public GameObject{
public:
	Player(ofPoint worldPosition, GameSprite* spt);
	~Player();
	void think();
	
	
	
	
};

#endif
