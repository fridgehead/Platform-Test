/*
 *  Map.h
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef	SPRITEY
#define SPRITEY


#include "SpriteManager.h"
#include "Sprite.h"
#include "ofMain.h"
#include "Camera.h"
#include "GameObject.h"

struct MapBlock{
	ImageData* sprite;
	bool breakable;
	bool collided;
};

class GameMap {
public:
	GameMap(SpriteManager* spriteMan, int width, int height);
	~GameMap();
	
	void loadFromFile(string file);
	//returns array indices of mapblocks in the map for a given area
	void getMapArea(ofRectangle area, GameSprite* blocks);
	void drawMap(Camera* cam);
	bool checkCollision(GameObject* subject);
	
	
	vector<GameSprite> mapData;
	int mapWidth, mapHeight;
	
	GameSprite* blockSprite[3];
	
private:
	SpriteManager* spriteManager;

	

};

#endif
