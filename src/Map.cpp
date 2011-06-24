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
	blockSprite[0]->collided = false;
	blockSprite[0]->think();

	blockSprite[1]= new GameSprite(spriteManager);
	blockSprite[1]->loadData("grassTiles");
	blockSprite[1]->setAnimation(TILE_MIDDLE);
	blockSprite[1]->think();	
	blockSprite[1]->collided = false;
	blockSprite[2] = new GameSprite(spriteManager);
	blockSprite[2]->empty = true;
	
	int ct = 0;
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			if(x % 3){
				mapData.push_back( *blockSprite[2]);
			} else {
				if(ofRandom(0,1) > 0.5f){
					mapData.push_back(	*blockSprite[0]);
				} else {
					ct++;
					blockSprite[1]->setAnimation((AnimationName)(6 + ct % 6));
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
					if(m->collided){
						ofSetColor(255, 0, 0);
					} else {
						ofSetColor(255, 255, 255);
					}
					m->draw(xp * 64 - (xShift),yp * 64 - (yShift),2);
				}
			} 
			
		}
	}
	
}

bool GameMap::checkCollision(GameObject* subject){
	
	//check for bb intersections with nearest blocks
	ofPoint subjectPos = subject->worldPos;
	ofPoint subjectBB = subject->boundingBoxSize;
	
	//find all tiles in the BB area
	int xMin = floor((subjectPos.x ) / 64);
	int yMin = floor((subjectPos.y ) / 64);
	int xMax = ceil((subjectPos.x + subjectBB.x ) / 64);
	int yMax = ceil((subjectPos.y + subjectBB.y ) / 64);	
	cout<< "!!!!!!!!!" << endl;
	for(int x = xMin; x < xMax; x++){
		for(int y = yMin; y < yMax; y++){	
			
			if( x < mapWidth && x > 0 && y < mapHeight && y  > 0){
				cout << "col: " << x << ":" << y << endl;
				mapData[x + y * mapWidth].collided = true;
			}
		}
	}
				
			
	
	return false;
	
}


void GameMap::loadFromFile(string file){

}

//returns array indices of mapblocks in the map for a given area
//not used because its SHIT
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

