/*
 *  SpriteManager.h
 *  Platform
 *
 *  loads sprite images, checks for sprites that have already been loaded and return the id's of them
 
 
 
*/

#ifndef SPRITEMANAGER
#define SPRITEMANAGER
#include "ofMain.h"

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();
	
	int loadImageFile(string imageFile);	//returns an int pointing at the image file in a vector
	
	vector<ofImage> spriteImages;
	
	
};

#endif