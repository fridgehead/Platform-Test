/*
 *  SpriteManager.cpp
 *  Platform
 *
 *  Created by Tom Wyatt on 22/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SpriteManager.h"

SpriteManager::SpriteManager(){
	spriteData.resize(0);
}
	
	
SpriteManager::~SpriteManager(){
}

ImageData* SpriteManager::getAnimationData(int spriteIndex, int name){
	
	vector<Animation>* anim = &(spriteData[spriteIndex].animations);
	vector<Animation>::iterator it;
	for( it = anim->begin(); it != anim->end(); it++){
		if(it->index == name){
			cout << "found it animation" << endl;
			return &spriteData[spriteIndex];
		}
	}
	return NULL;
}



int SpriteManager::loadDataFile(string tag){
	
	
	//check the sprite is loaded and return an int, if not then load it and return int
	vector<ImageData>::iterator it;
	for( it = spriteData.begin(); it != spriteData.end(); it++){
		if(it->tag == tag){
		//	cout << "found it!" << endl;
			return it - spriteData.begin();
		}
	}
	ImageData temp;
	
	//ok so we didnt find it, load it up!
	//cout << "loading .. " << tag << endl;
	temp.tag = tag;
	xml.loadFile(ofToDataPath(tag + ".xml"));
	//get our image
	string img = xml.getAttribute("image", "file", "none", 0);
	temp.image.loadImage(img);
	
	int x = xml.getAttribute("animations", "width", 0.0, 0);
	int y = xml.getAttribute("animations", "height", 0.0, 0);
	
	temp.dimensions = ofPoint(x,y);
	int numAnims = xml.getAttribute("animations", "num", 0.0, 0);
	//cout << "num anims " << numAnims << endl;
	int animId;
	int rowId;
	int frameLength;
	int frameSpeed;
	xml.pushTag("animations", 0);
	for(int an = 0; an < numAnims; an++){
		xml.pushTag("anim", an);
		animId = xml.getAttribute("index", "id", 0.0, 0);	//matches the enums for animation types
		rowId = xml.getAttribute("row", "id", 0.0, 0);
		frameLength = xml.getAttribute("frames", "length", 0.0, 0);	
		frameSpeed = xml.getAttribute("frames", "speed", 10.0, 0);	

		Animation a;
		a.numFrames = frameLength;
		a.index = animId;
		a.spriteRow = rowId;
		a.animSpeed = frameSpeed;
		temp.animations.push_back(a);
		
		
		xml.popTag();
	}
	xml.popTag();
	
	spriteData.push_back(temp);
	return spriteData.size() - 1;
	
}





