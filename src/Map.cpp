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


#define	COL_NONE 0
#define	COL_TOP  1
#define	COL_RIGHT  2
#define	COL_BOTTOM  3
#define	COL_LEFT  4


GameMap::GameMap(SpriteManager* spriteMan, int width, int height){
	spriteManager = spriteMan;
	mapWidth = width;
	mapHeight = height;
	

	blockSprite[0]= new GameSprite(spriteManager);
	blockSprite[0]->loadData("block");
	blockSprite[0]->setAnimation(ANIM_WALK);
	blockSprite[0]->setCurrentFrame(0);
	blockSprite[0]->collided = false;
	blockSprite[0]->think();

	blockSprite[1]= new GameSprite(spriteManager);
	blockSprite[1]->loadData("grassTiles");
	blockSprite[1]->setAnimation(TILE_MIDDLE);
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
					//blockSprite[1]->setAnimation((AnimationName)(6 + ct % 6));
					mapData.push_back(	*blockSprite[2]);
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
	
	bool didWeCollide = false;
	int collisions = COL_NONE;
	
	bool onGround = false;
	//subject->isOnGround = false;
	for(int x = xMin; x < xMax; x++){
		for(int y = yMin; y < yMax; y++){	
			
			if( x < mapWidth && x > 0 && y < mapHeight && y  > 0){
				//these are tiles we are likely to collide with
				GameSprite* b = &mapData[x + y * mapWidth];
				if(b->empty != true ){
					collisions = COL_NONE;
					b->collided = true;
					//do a smooth pixel collision test.
					//return the hit position
					//if were falling then stop us
					
					
					//cout << ": player base pos: " << subject->worldPos.y + subjectBB.y  << " -- block pos " << y * 64<< endl;
					
					//check bottom edge is inside the collided tile
					if((subjectPos.y + subjectBB.y) > (y * 64 ) && (subjectPos.y + subjectBB.y) <  (y * 64 ) + 64){
						if( subject->isOnGround == false){
							//hit the ground
							
							onGround = true;
							subject->speed.y = 0;
							subject->worldPos.y = ((y * 64 ) - subjectBB.y )  ;
							//cout << "set: " << subject->worldPos.y << endl;
							
							subject->isJumping = false;
							didWeCollide = true;
							collisions |= COL_BOTTOM;
							
						}  else {
							subject->speed.y = 0;
							subject->worldPos.y = ((y * 64 ) - subjectBB.y )  ;
							didWeCollide = true;
							onGround = true;
							collisions |= COL_BOTTOM;
						}
							
					}
					//right side of subject, left of block
					if((subjectPos.x + subjectBB.x) >= (x * 64 ) && (subjectPos.x + subjectBB.x) <=  (x * 64 ) + 64 &&  collisions == COL_NONE){
						subject->speed.x = 0;
						subject->worldPos.x = ((x * 64 ) - subjectBB.x ) ;
						collisions |= COL_LEFT;
					}
					//left of object, right of block
					if((subjectPos.x ) >= (x * 64 ) && (subjectPos.x) <=  (x * 64 ) + 64 && collisions == COL_NONE){
						subject->speed.x = 0;
						subject->worldPos.x = ((x * 64 ) + 64 )  ;
						collisions |= COL_RIGHT;
					}
					
					//top of object, bottom of block
					if((subjectPos.y ) >= (y * 64 ) && (subjectPos.y) <=  (y * 64 ) + 64 && collisions == COL_NONE){
						subject->speed.y = 0;
						subject->worldPos.y = ((y * 64 )  + 64)  ;
						collisions |= COL_TOP;
					}
					
				}
				
			}
		}
	}
	subject->isOnGround = onGround;
	
	return didWeCollide;
	
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

