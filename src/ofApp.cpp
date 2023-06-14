#include "ofApp.h"
#include <thread>
#include <chrono>

//--------------------------------------------------------------
void ofApp::setup(){

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    m_lives = 3;
    m_collectedAllFruits = false;
    m_davesGoal.set(screenWidth * 0.95, 0, 50, 50);
    m_player = new Player(screenWidth / 2, screenHeight * 0.95);
    m_enemies = new vector<Enemy>{Enemy(screenWidth * 0.25, screenHeight * 0.25, screenWidth * 0.02), Enemy(screenWidth * 0.5, screenHeight * 0.5, screenWidth * 0.015), Enemy(screenWidth * 0.50, screenHeight * 0.75, screenWidth * 0.01)};
    m_fruits = new vector<Fruit>{Fruit(), Fruit(), Fruit()};
}

//--------------------------------------------------------------
void ofApp::update(){
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    if(m_lives <= 0){//lives are 0, game over. No need to check for collisions
        return;
    }
    checkEnemyCollision();
    m_collectedAllFruits ? checkIfGoalReached() : checkFruitCollection();
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofBackground(255, 255, 255);

    if(m_goalReached){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("You Win!\nHit SPACE to start again or Q to quit", screenWidth * 0.50, screenHeight * 0.50);
        return;
    }
    
    if(m_lives <= 0){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Game Over\nHit SPACE to start again or Q to quit", screenWidth * 0.50, screenHeight * 0.50);
        return;
    }

    ofDrawBitmapString(getLivesText(), 10, 20);

    ofSetColor(0, 255, 0);
    if(m_collectedAllFruits){
    ofDrawRectangle(m_davesGoal);
    }

    m_player->drawElement();
    drawEnemies();
    drawFruits();
}

//Listen for key presses. If the space bar is pressed, reset the game. If the q key is pressed, quit the game. Otherwise, move the avatar.
void ofApp::keyPressed(int key){

    if(key == ' '){
        m_lives = 3;
        m_goalReached = false;
        //m_player->resetAvatar();
        delete m_player;
        delete m_enemies;
        delete m_fruits;
        setup();
    }
    else if(key == 'q'){
        ofExit();
    }
    m_player->movePlayer(key);
}

void ofApp::checkEnemyCollision(){
    for(int i = 0; i < m_enemies->size(); i++){
        if(m_player->m_collisionBox.intersects(m_enemies->at(i).m_collisionBox)){
            m_lives--;
            m_player->resetPlayer();
        }
    }
}

void ofApp::checkFruitCollection(){
    m_fruitMutex.lock();
    for(int i = 0; i < m_fruits->size(); i++){
            if(m_player->m_collisionBox.intersects(m_fruits->at(i).m_collisionBox)){
                m_fruits->erase(m_fruits->begin() + i);
            }
            if(m_fruits->size() == 0){
            m_collectedAllFruits = true;}
    }
    m_fruitMutex.unlock();
}

void ofApp::checkIfGoalReached(){
    if(m_player->m_collisionBox.intersects(m_davesGoal)){
        m_goalReached = true;
        m_player->resetPlayer();
        return;
    }
}

void ofApp::startTimerThread(){
    std::thread timerThread = std::thread(startTimer());
}

void ofApp::startTimer(){
    while(!m_collectedAllFruits && !m_fruits->empty()){
        std::this_thread::sleep_for(std::chrono::seconds(30));
        shuffleFruits();
    }
}

void ofApp::drawEnemies(){
    for(int i = 0; i < m_enemies->size(); i++){
            m_enemies->at(i).moveEnemy();
            m_enemies->at(i).drawElement();
        }
}

void ofApp::drawFruits(){
    m_fruitMutex.lock();
    for(int i = 0; i < m_fruits->size(); i++){
        m_fruits->at(i).drawElement();
    }
    m_fruitMutex.unlock();
}

std::string ofApp::getLivesText(){
    switch(m_lives){
        case 3:
            return "Lives: 3";
        case 2:
            return "Lives: 2";
        case 1:
            return "Lives: 1";
        default:
            return "error";
    }
}

GuiElement::GuiElement(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}

GuiElement::~GuiElement() {}

void GuiElement::drawElement(){}

//Creates an Enemy and calls the drawElement function.
Enemy::Enemy(int xPos, int yPos, int movementSpeed)
    :  GuiElement(xPos, yPos), m_movementSpeed(movementSpeed){
}

//Sets up the collision box for an enemy. This is used to determine if the user intersects this element.
void Enemy::drawElement(){
    m_collisionBox.set(m_xPos,m_yPos, ENEMY_WIDTH, ENEMY_HEIGHT);
    ofSetColor(255, 155, 0);
    ofDrawRectangle(m_xPos,m_yPos, ENEMY_WIDTH, ENEMY_HEIGHT);
}

void Enemy::moveEnemy(){
    int screenWidth = ofGetWidth();
    if (m_moveRight) {
       if(m_xPos <= screenWidth - 200){ 
        if(m_movementSpeed <= screenWidth * 0.01){
            m_xPos += m_movementSpeed * 1.5;
        }
           else{
               m_xPos += m_movementSpeed;
           } 
       }
        else{
            m_moveRight = false;
        }
    }
    else if(!m_moveRight){
        if(m_xPos >= 0){
            if(m_moveRight > screenWidth * 0.01){
                m_xPos -= m_movementSpeed * 0.75;
            }
            else{
                m_xPos -= m_movementSpeed;
            }
            } //slower than moveRight to make it more interesting
        if(m_xPos <= 0){
            m_moveRight = true; 
        }
    }
}

//Creates a player and calls the drawElement function.
Player::Player(int topVertexXpos, int topVertexYpos)
    :  GuiElement(topVertexXpos, topVertexYpos){
}

void Player::resetPlayer(){
    m_xPos = ofGetWidth() * 0.5;
    m_yPos = ofGetHeight() * 0.95;
}

//Sets up the collision box for the player character. This is used to determine if the player intersects other element.
void Player::drawElement(){
    m_collisionBox.set(m_xPos - PLAYER_WIDTH/2, m_yPos, PLAYER_WIDTH, PLAYER_HEIGHT);
    ofSetColor(0, 0, 0);
    ofDrawTriangle(m_xPos, m_yPos, m_xPos - PLAYER_WIDTH/2, m_yPos + PLAYER_HEIGHT , m_xPos + PLAYER_WIDTH/2,  m_yPos + PLAYER_HEIGHT);
}

//moves the avatar. The avatar can move up, down, left, or right. The avatar cannot move off the screen.
void Player::movePlayer(int direction){
    int screenWidth = ofGetWidth();
    int screenHeight = ofGetHeight();
    switch(direction){
        case 'w':
            if(m_yPos >= 0)
            {
                m_yPos -= screenHeight * 0.015;
            }
            break;
        case 's':
            if(m_yPos <= screenHeight)
            {
                m_yPos += screenHeight * 0.015;
            }
            break;
        case 'a':
            if(m_xPos >= 10)
            {
                m_xPos -= screenWidth * 0.015;    
            }
            break;
        case 'd':
            if(m_xPos <= screenWidth - 10)
            {
                m_xPos += screenWidth * 0.015;
            }
            break;
    }
}

//Creates a Fruit and calls the drawElement function.
Fruit::Fruit() 
		: GuiElement(rand() % ofGetScreenWidth() + FRUIT_RADIUS * 2, rand() % ofGetScreenHeight() + FRUIT_RADIUS * 2){
            m_collected = false;
}

void Fruit::drawElement(){
    m_collisionBox.set(m_xPos, m_yPos, FRUIT_RADIUS * 2, FRUIT_RADIUS * 2);
    ofSetColor(255, 0, 0);
    ofDrawCircle(m_xPos, m_yPos, FRUIT_RADIUS);
}

void Fruit::shuffleLocation(){
    m_xPos = rand() % ofGetScreenWidth() + FRUIT_RADIUS * 2;
    m_yPos = rand() % ofGetScreenHeight() + FRUIT_RADIUS * 2;
}

void ofApp::shuffleFruits(){
    m_fruitMutex.lock();
    for(auto fruit : *m_fruits){
        fruit.shuffleLocation();
    }
    m_fruitMutex.unlock();
}