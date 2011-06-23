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
}

GameObject::~GameObject(){

}

Player::Player(ofPoint worldPosition, GameSprite* spt) : GameObject(worldPosition, spt){
}


Player::~Player(){
	
}

void Player::think(){
	sprite->think();
}

