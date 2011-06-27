/*
 *  SpriteManager.h
 *  Platform
 *
 *  loads sprite images, checks for sprites that have already been loaded and return the id's of them
 
 
 
*/

#ifndef SPRITEMANAGER
#define SPRITEMANAGER
#include "ofMain.h"
#include "ofxXmlSettings.h"

struct Animation{
	int numFrames;	//number of frames
	int index;		//animation name
	int spriteRow;	//row in sprite sheet
	int animSpeed;
	int collisionMask;
};

struct ImageData {
	string tag;
	
	ofImage image;
	ofPoint dimensions;

	vector<Animation> animations;
	//bool operator==(const string& a){ return tag == a; };
	
};

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();
	
	int loadDataFile(string tag);	//returns an int pointing at the image file in a vector
	
	vector<ImageData> spriteData;
	ImageData* getAnimationData(int spriteIndex, int name);
	
private:
	ofxXmlSettings xml;
	
};

#endif