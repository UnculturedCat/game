#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Dodger Dave");
    ofSetVerticalSync(true);
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    lives = 3;
    davesGoal.set(screenWidth * 0.95, 0, 50, 50);
    player = new avatar(screenWidth / 2, screenHeight * 0.95);
    enemies = new vector<enemy>{enemy(screenWidth * 0.25, screenHeight * 0.25, screenWidth * 0.02, false, true), enemy(screenWidth * 0.5, screenHeight * 0.5, screenWidth * 0.015, true, false), enemy(screenWidth * 0.50, screenHeight * 0.75, screenWidth * 0.01, false, true)};
}

//--------------------------------------------------------------
void ofApp::update(){
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    

    if(lives <= 0){//lives are 0, game over. No need to check for collisions
        return;
    }
   
    if(player->avatarShape.intersects(davesGoal)){
        goalReached = true;
        player->resetAvatar();
        return;
    }

    for(int i = 0; i < enemies->size(); i++){
        if(player->avatarShape.intersects(enemies->at(i).enemyShape)){
            lives--;
            player->resetAvatar();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);

    if(goalReached){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("You Win!\nHit SPACE to start again or Q to quit", screenWidth * 0.50, screenHeight * 0.50);
        return;
    }
    
    if(lives <= 0){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Game Over\nHit SPACE to start again or Q to quit", screenWidth * 0.50, screenHeight * 0.50);
        return;
    }
    if(lives == 3){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Lives: 3", 10, 20);
    }
    else if(lives == 2){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Lives: 2", 10, 20);
    }
    else if(lives == 1){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Lives: 1", 10, 20);
    }

    ofSetColor(0, 255, 0);
    ofDrawRectangle(davesGoal);

    player->drawAvatar();
    for(int i = 0; i < enemies->size(); i++){
        enemies->at(i).moveEnemy();
        enemies->at(i).drawEnemy();
    }
}

//Listen for key presses. If the space bar is pressed, reset the game. If the q key is pressed, quit the game. Otherwise, move the avatar.
void ofApp::keyPressed(int key){

    if(key == ' '){
        lives = 3;
        goalReached = false;
        player->resetAvatar();
    }
    else if(key == 'q'){
        ofExit();
    }
    player->moveAvatar(key);
}

avatar::avatar(int xPos, int yPos){
    this->xPos = xPos;
    this->yPos = yPos;
    this->avatarShape.set(xPos, yPos, 50, 50);
}

//draws the avatar. The avatar is a rectangle with a black outline and fill.
void avatar::drawAvatar(){
    ofSetColor(0, 0, 0);
    this->avatarShape.set(this->xPos, this->yPos, 50, 50);
    ofDrawRectangle(this->avatarShape);
}

//moves the avatar. The avatar can move up, down, left, or right. The avatar cannot move off the screen.
void avatar::moveAvatar(int direction){
    int screenWidth = ofGetWidth();
    int screenHeight = ofGetHeight();
    switch(direction){
        case 'w':
            if(this->yPos >= 0)
            {
                this->yPos -= screenHeight * 0.015;
            }
            break;
        case 's':
            if(this->yPos <= screenHeight)
            {
                this->yPos += screenHeight * 0.015;
            }
            break;
        case 'a':
            if(this->xPos >= 0)
            {
                this->xPos -= screenWidth * 0.015;    
            }
            break;
        case 'd':
            if(this->xPos <= screenWidth - 50)
            {
                this->xPos += screenWidth * 0.015;
            }
            break;
    }
}

//resets the avatar to the bottom center of the screen.
void avatar::resetAvatar(){
    this->xPos = ofGetWidth() / 2;
    this->yPos = ofGetHeight() * 0.95;
    this->avatarShape.set(this->xPos, this->yPos, 50, 50);
}

//creates an enemy. The enemy is a rectangle with a orange outline and orange fill.
enemy::enemy(int xPos, int yPos, int speed, bool moveRight, bool moveLeft){
    this->xPos = xPos;
    this->yPos = yPos;
    this->speed = speed;
    this->moveRight = moveRight;
    this->moveLeft = moveLeft;
    this->enemyShape.set(xPos, yPos, 200, 100);
}

//draws the enemy. fill is orange, outline is orange.
void enemy::drawEnemy(){
    this->enemyShape.set(this->xPos, this->yPos, 200, 100);
    ofSetColor(255, 155, 0);
    ofDrawRectangle(this->enemyShape);
}

//moves the enemy. The enemy moves back and forth across the screen with varying speeds. The enemy cannot move off the screen.
void enemy::moveEnemy(){
    int screenWidth = ofGetWidth();
    int screenHeight = ofGetHeight();
    if (moveRight) {
       if(this->xPos <= screenWidth - 200){ 
        if(speed <= screenWidth * 0.01){
            this->xPos += speed * 1.5;
        }
           else{
               this->xPos += speed;
           } 
       }
        else{
            this->moveRight = false;
            this->moveLeft = true;
        }
    }
    else if(moveLeft){
        if(this->xPos >= 0){
            if(speed > screenWidth * 0.01){
                this->xPos -= speed * 0.75;
            }
            else{
                this->xPos -= speed;
            }
            } //slower than moveRight to make it more interesting
        if(this->xPos <= 0){
            this->moveRight = true;
            this->moveLeft = false;
        }
    }
    drawEnemy();
}