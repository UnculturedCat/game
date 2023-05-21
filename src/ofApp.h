#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int mouseX;
		int mouseY;

		int lives;
		int score;

		ofColor fillColor;
		ofRectangle player;
		ofRectangle enemy;
		ofRectangle enemy2;	
		ofRectangle enemy3;
		int xpos;
		bool moveRight;
		bool moveLeft;

		int playerXpos;
		int playerYpos;
		int screenWidth;
		int screenHeight;
};

class player{
	public:

	void drawPlayer();

};