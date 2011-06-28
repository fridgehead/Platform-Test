/*
 *  GameObject.cpp
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameObject.h"

GameObject::GameObject(ofPoint worldPosition, GameSprite* spt){

	worldPos = worldPosition;
	sprite = spt;
	speed = ofPoint(0,0);
	isOnGround = false;
//	boundingBox = ofRectangle(0,0,sprite->boundingBox.x, sprite->boundingBox.y);
}

GameObject::~GameObject(){

}

ofRectangle GameObject::getBoundingBox(){
	return sprite->boundingBox;
}

Player::Player(ofPoint worldPosition, GameSprite* spt) : GameObject(worldPosition, spt){
}


Player::~Player(){
	
}


void Player::think(){
	if(isOnGround){
	
		speed.y = 0;
		//cout << "ground " << endl;
		isJumping = false;
	} else {
		//cout << "not ground" << endl;
		isJumping = true;
		if(speed.y < 30){
			speed.y += 2;
		}
	}
	worldPos.y += speed.y;
	worldPos.x += speed.x;
	sprite->think();
	
	
}


void Player::collided(GameObject* subject){
	cout << "hit something" << endl;
}



