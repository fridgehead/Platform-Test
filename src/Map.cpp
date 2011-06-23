/*
 *  Map.cpp
 *  Platform
 *
 *  Created by Tom Wyatt on 23/06/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Map.h"
#include "Camera.h"

GameMap::GameMap(SpriteManager* spriteMan, int width, int height){
	spriteManager = spriteMan;
	mapWidth = width;
	mapHeight = height;
	

	blockSprite[0]= new GameSprite(spriteManager);
	blockSprite[0]->loadData("block");
	blockSprite[0]->setAnimation(ANIM_WALK);

	blockSprite[1]= new GameSprite(spriteManager);
	blockSprite[1]->loadData("rock");
	blockSprite[1]->setAnimation(ANIM_WALK);
	
	blockSprite[2] = new GameSprite(spriteManager);
	blockSprite[2]->empty = true;
	
	
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			if(x % 3){
				mapData.push_back( *blockSprite[2]);
			} else {
				if(ofRandom(0,1) > 0.5f){
					mapData.push_back(	*blockSprite[0]);
				} else {
					mapData.push_back(	*blockSprite[1]);
				}
			}
			
		}
	}
	
	
}

GameMap::~GameMap(){


}

void GameMap::drawMap(Camera* cam){
	//work out whats in view
	int xCount = floor(cam->size.x / 64.0f) + 1;
	int yCount = floor(cam->size.y / 64.0f)  +1;
	
	int xMin = floor(cam->worldPosition.x / 64);
	int yMin = floor(cam->worldPosition.y / 64);
	
	int xShift = ((int)cam->worldPosition.x % 64);// - xMin;
	int yShift = ((int)cam->worldPosition.y % 64);// - yMin;
	
	//cout << xShift << endl;
	for(int xp = 0; xp < xCount; xp++){
		for(int yp = 0; yp < yCount; yp++){
			
			if( xMin + xp < mapWidth && xp + xMin > 0 && yp + yMin < mapHeight && yp + yMin > 0){
				GameSprite* m = &mapData[(xp + xMin) + (yp + yMin) * mapWidth];
				if(m->empty == false){
					m->think();
					//m->pos = ofPoint(xp * 32, yp * 32);
					m->draw(xp * 64 - (xShift),yp * 64 - (yShift),2);
				}
			} 
			
		}
	}
	
	/*
	for(int xp = 0; xp < w; xp++){
		for(int yp = 0; yp < h; yp++){
			
			if( x + xp < mapWidth && xp + x > 0 && yp + y < mapWidth && yp + y > 0){
				GameSprite* m = &mapData[(xp + x) + (yp + y) * mapWidth];
				if(m->empty == false){
					m->think();
					//m->pos = ofPoint(xp * 32, yp * 32);
					m->draw(xp *32 * 2,yp * 32 * 2,2);
				}
			} 
			
		}
	}*/
	
}


void GameMap::loadFromFile(string file){

}

//returns array indices of mapblocks in the map for a given area
void GameMap::getMapArea(ofRectangle area, GameSprite* blocks){
	int w = (int)area.width;
	int h = (int)area.height;
	
	blocks = new GameSprite[w * h];
	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			blocks[x + y * w].spriteMan = spriteManager;
			if( area.x + x < mapWidth && area.x + x > 0 && area.y + y < mapWidth && area.y + y > 0){
				blocks[x + y * w] = mapData[((int)area.x + x) + ((int)area.y + y) * mapWidth];
			} 
				
		}
	}
	
													 
			
}

