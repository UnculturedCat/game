#pragma once

#include "ofMain.h"

class avatar{
	private:
		int xPos;
		int yPos;
	
	public: 
		ofRectangle avatarShape;
		avatar(int xPos, int yPos);
		void drawAvatar();
		void moveAvatar(int direction);
		void resetAvatar();
};

class enemy{
	private:
		int xPos;
		int yPos;
		int speed;
		bool moveRight;
		bool moveLeft;
	
	public:
		enemy(int xPos, int yPos, int speed, bool moveRight, bool moveLeft);
		void drawEnemy();
		void moveEnemy();
		ofRectangle enemyShape;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		bool goalReached;

		int lives;
		int score;

		int screenWidth;
		int screenHeight;

		
		ofRectangle davesGoal;
		avatar* player;
		vector<enemy>* enemies;
};