/*
 *  Camera.h
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAM
#define CAM
#include "ofMain.h"


class Camera{
	public:
	Camera(int screenWidth, int screenHeight);
	~Camera();

	ofPoint worldPosition;
	ofPoint size;
	ofPoint screenToWorld(ofPoint in);
	ofPoint worldToScreen(ofPoint in);
};
#endif