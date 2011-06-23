/*
 *  Camera.cpp
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight){
	worldPosition = ofPoint (0,0);
	size.x = screenWidth;
	size.y = screenHeight;
}

Camera::~Camera(){}


ofPoint Camera::screenToWorld(ofPoint in){
	
	ofPoint t;
	t.x = in.x + worldPosition.x;
	t.y = in.y + worldPosition.y;
	return t;
	
	
}

ofPoint Camera::worldToScreen(ofPoint in){
	ofPoint t;
	t.x = (worldPosition.x + size.x) - in.x;
	t.y = (worldPosition.y + size.y) - in.y;
	
	
	if(t.x > -150 && t.x < size.x + 150 && t.y > -150 && t.y < size.y + 150){
		return size - t;
	} else {
		t = ofPoint(-1,-1);
		return t;
	}
}