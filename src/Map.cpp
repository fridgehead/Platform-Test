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
#include <iostream>


#define	COL_NONE 0
#define	COL_TOP  1
#define	COL_RIGHT  2
#define	COL_BOTTOM  3
#define	COL_LEFT  4




GameMap::GameMap(SpriteManager* spriteMan, int width, int height){
	spriteManager = spriteMan;
	mapWidth = width;
	mapHeight = height;
	
	BLOCKSIZE = 32.0f;
		
	
}

GameMap::~GameMap(){


}

void GameMap::drawMap(Camera* cam){
	//work out whats in view
	int xCount = floor(cam->size.x / BLOCKSIZE) + 1;
	int yCount = floor(cam->size.y / BLOCKSIZE) +1;
	
	int xMin = floor(cam->worldPosition.x / BLOCKSIZE);
	int yMin = floor(cam->worldPosition.y / BLOCKSIZE);
	
	int xShift = ((int)cam->worldPosition.x % (int)BLOCKSIZE);// - xMin;
	int yShift = ((int)cam->worldPosition.y % (int)BLOCKSIZE);// - yMin;
	
	//cout << xShift << endl;
	for(int xp = 0; xp < xCount; xp++){
		for(int yp = 0; yp < yCount; yp++){
			
			if( xMin + xp < mapWidth && xp + xMin > 0 && yp + yMin < mapHeight && yp + yMin > 0){
				GameSprite* m = &mapData[(xp + xMin) + (yp + yMin) * mapWidth];
				if(m->empty == false){
					m->think();
					//m->pos = ofPoint(xp * 32, yp * 32);
					if(m->collided){
						//ofSetColor(255, 0, 0);
					} else {
						//ofSetColor(255, 255, 255);
					}
					m->draw(xp * BLOCKSIZE - (xShift),yp * BLOCKSIZE - (yShift),1);

				} else {
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
	int xMin = floor((subjectPos.x ) / BLOCKSIZE);
	int yMin = floor((subjectPos.y ) / BLOCKSIZE);
	int xMax = ceil((subjectPos.x + subjectBB.x ) / BLOCKSIZE);
	int yMax = ceil((subjectPos.y + subjectBB.y ) / BLOCKSIZE);	
	
	bool didWeCollide = false;
	int collisions = COL_NONE;
	
	bool onGround = false;
	//subject->isOnGround = false;
	for(int x = xMin; x < xMax; x++){
		for(int y = yMin; y < yMax; y++){	
			
			if( x < mapWidth && x > 0 && y < mapHeight && y  > 0){
				//these are tiles we are likely to collide with
				GameSprite* b = &mapData[x + y * mapWidth];
				if(b->empty == false ){
					collisions = COL_NONE;
					b->collided = true;
					b->setCurrentFrame(0);
					//do a smooth pixel collision test.
					//return the hit position
					//if were falling then stop us
					
					
					//cout << ": player base pos: " << subject->worldPos.y + subjectBB.y  << " -- block pos " << y * BLOCKSIZE<< endl;
					
					//check bottom edge is inside the collided tile
					if((subjectPos.y + subjectBB.y) > (y * BLOCKSIZE ) && (subjectPos.y + subjectBB.y) <  (y * BLOCKSIZE ) + BLOCKSIZE){
						if( subject->isOnGround == false){
							//hit the ground
							
							onGround = true;
							subject->speed.y = 0;
							subject->worldPos.y = ((y * BLOCKSIZE ) - subjectBB.y )  ;
							//cout << "set: " << subject->worldPos.y << endl;
							
							subject->isJumping = false;
							didWeCollide = true;
							collisions |= COL_BOTTOM;
							
						}  else {
							subject->speed.y = 0;
							subject->worldPos.y = ((y * BLOCKSIZE ) - subjectBB.y )  ;
							didWeCollide = true;
							onGround = true;
							collisions |= COL_BOTTOM;
						}
							
					} else if((subjectPos.y ) >= (y * BLOCKSIZE ) && (subjectPos.y) <=  (y * BLOCKSIZE ) + BLOCKSIZE ){
						subject->speed.y = 0;
						subject->worldPos.y = ((y * BLOCKSIZE )  + BLOCKSIZE)  ;
						collisions |= COL_TOP;
					}
					
					//right side of subject, left of block
					if((subjectPos.x + subjectBB.x) >= (x * BLOCKSIZE ) && (subjectPos.x + subjectBB.x) <=  (x * BLOCKSIZE ) + BLOCKSIZE &&  collisions == COL_NONE){
						subject->speed.x = 0;
						subject->worldPos.x = ((x * BLOCKSIZE ) - subjectBB.x ) ;
						collisions |= COL_LEFT;
					}
					//left of object, right of block
					if((subjectPos.x ) >= (x * BLOCKSIZE ) && (subjectPos.x) <=  (x * BLOCKSIZE ) + BLOCKSIZE && collisions == COL_NONE){
						subject->speed.x = 0;
						subject->worldPos.x = ((x * BLOCKSIZE ) + BLOCKSIZE )  ;
						collisions |= COL_RIGHT;
					}			
										
				}
				
			}
		}
	}
	subject->isOnGround = onGround;
	
	return didWeCollide;
	
}


void GameMap::loadFromFile(string file){
	
	tmxMap = new Tmx::Map();
	tmxMap->ParseFile(ofToDataPath("test.tmx"));
	cout << "====laoding tmx map =====" << endl;
	if (tmxMap->HasError()) {
		printf("error code: %d\n", tmxMap->GetErrorCode());
		printf("error text: %s\n", tmxMap->GetErrorText().c_str());
	} else {
		cout << "LOADED MAP" << endl;
	}
	// Iterate through the tilesets.
	for (int i = 0; i < tmxMap->GetNumTilesets(); ++i) {
		printf("                                    \n");
		printf("====================================\n");
		printf("Tileset : %02d\n", i);
		printf("====================================\n");
		
		// Get a tileset.
		const Tmx::Tileset *tileset = tmxMap->GetTileset(i);
		
		// Print tileset information.
		printf("Name: %s\n", tileset->GetName().c_str());
		// Get a tile from the tileset.
			
	
			
	
	}
	
	// Iterate through ttmxMap->he layers.
	for (int i = 0; i < tmxMap->GetNumLayers(); ++i) {
		mapWidth =  tmxMap->GetLayer(i)->GetWidth() ;
		mapHeight =  tmxMap->GetLayer(i)->GetHeight() ;

		printf("                                    \n");
		printf("====================================\n");
		printf("Layer : %02d/%s \n", i, tmxMap->GetLayer(i)->GetName().c_str());
		printf("width : %02d \n", mapWidth);
		printf("height : %02d \n", mapHeight);
		printf("====================================\n");
       		
		// Get a layer.
		const Tmx::Layer *layer = tmxMap->GetLayer(i);
		
		for (int y = 0; y < mapHeight; ++y) {
			for (int x = 0; x < mapWidth; ++x) {

				// Get a tile global id.
				//printf("%03d ", layer->GetTileGid(y, x));
				// Find a tileset for that id.
				const Tmx::Tileset *tileset = tmxMap->FindTileset(layer->GetTileGid(x,y));
				if(tileset != 0){
					int firstGid = tileset->GetFirstGid();
					//convert the tile gid to an animation enum
					
					int anim = layer->GetTileGid(x,y) - firstGid;
					if(anim >6) {
						cout << "!!!!!!" << endl;
						cout << x <<":" << y <<endl;
						cout << anim << endl;
					}
					//cout << anim;
					
					 GameSprite* gs = new GameSprite(spriteManager);
					 //get the xml block file name from the image source name
					 string imgName = tileset->GetImage()->GetSource();
					 int pos = imgName.find(".");
					 imgName.replace(pos, 4, "");
										
					 gs->loadData(imgName);
					 gs->collided = false;
					gs->empty = false;
					gs->setAnimation(anim);
					
					gs->setCurrentFrame(0);
					cout << anim;
					
					 mapData.push_back(*gs);
					 delete gs;
				} else {
					GameSprite* gs = new GameSprite(spriteManager);
					gs->empty=true;
					gs->collided = false;
					mapData.push_back(*gs);
					delete gs;
					cout << " ";
				}
				
			}
			cout << endl;
		}
	}
	
	
	
	delete tmxMap;
	
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

