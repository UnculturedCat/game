#pragma once

#include "ofMain.h"

#define ENEMY_HEIGHT 100
#define ENEMY_WIDTH 200
#define PLAYER_WIDTH 70
#define PLAYER_HEIGHT 70
#define FRUIT_RADIUS 20


class GuiElement {

	public:
		int m_xPos, m_yPos;
		ofRectangle m_collisionBox;
		
		GuiElement(int xPos, int yPos);
		virtual ~GuiElement();

		virtual void drawElement(); //Apparently virtual functions are costly because of the extra steps

		
};


class Enemy : public GuiElement {

	private:
		int m_movementSpeed;
		bool m_moveRight;
	
	public:
		Enemy(int xPos, int yPos, int movementSpeed);

		void drawElement();
		void moveEnemy();
};

class Player : public GuiElement {
	
	public:
		Player(int topVertexXpos, int topVertexYpos);
		
		void drawElement();
		void movePlayer(int direction);
		void resetPlayer();
};

class Fruit : public GuiElement {
	
	public:
		bool m_collected;
		Fruit() ;

		void drawElement();
};

class ofApp : public ofBaseApp{

	public:
		bool m_goalReached;
		bool m_collectedAllFruits;

		int m_lives;

		int screenWidth;
		int screenHeight;

		
		ofRectangle m_davesGoal;
		Player* m_player;
		vector<Enemy>* m_enemies;
		vector<Fruit>* m_fruits;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};