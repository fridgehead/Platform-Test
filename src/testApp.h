#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Map.h"
#include "Camera.h"
#include "GameObject.h"

//#define DEBUG

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	GameSprite* sprite;
	GameSprite* testSprite;
	SpriteManager spriteManager;
	GameMap* gameMap;
	Camera* camera;
	ofImage test;
	Player* testPlayer;
	
	AnimationName t;
	int playerX,playerY;
	int dir;
	
	
	bool ready;
	
	
	ofImage watermark;
	ofImage backgroundImage;
};

#endif
