#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofApp");
    ofSetVerticalSync(true);
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    fillColor.set(255, 155, 0);
    xpos = 0;
    lives = 3;
    moveRight = true;
    moveLeft = false;
    playerXpos = screenWidth / 2;
    playerYpos = screenHeight - 100;
}

//--------------------------------------------------------------
void ofApp::update(){
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);
    
    if(lives == 0){
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("Game Over\nHit SPACE to start again", screenWidth * 0.50, screenHeight * 0.50);
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

    player.set(playerXpos, playerYpos, 50, 50);
    
    enemy.set(screenWidth * 0.25, screenHeight * 0.25, 50, 50);
    enemy2.set(screenWidth * 0.75, screenHeight * 0.75, 50, 50);
    
  
    
    ofSetColor(255, 0, 0);
    if (moveRight == true) {
       if(xpos <= screenWidth - 200){ 
            xpos += 5;
       }
        else{
            moveRight = false;
            moveLeft = true;
        }
        enemy3.set(xpos, screenHeight * 0.50, 200, 100);
        ofDrawRectangle(enemy3);
    }
    else if(moveLeft == true){
        if(xpos >= 0)
            xpos -= 10;
        if(xpos <= 0){
            moveRight = true;
            moveLeft = false;
        }
        enemy3.set(xpos, screenHeight * 0.50, 200, 100);
        ofDrawRectangle(enemy3);
    }

   
    
    // ofTriangle(mouseX, mouseY, mouseX + 50, mouseY + 50, mouseX - 50, mouseY + 50);
   
    ofDrawRectangle(enemy);
    ofDrawRectangle(enemy2);
    if(player.intersects(enemy) || player.intersects(enemy2) || player.intersects(enemy3)) {
        lives--;
        playerXpos = screenWidth / 2;
        playerYpos = screenHeight - 100;
    }
    ofSetColor(fillColor);
    ofDrawRectangle(player);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == ' '){
        lives = 3;
    }
    else if(key == 'q'){
        ofExit();
    }
    if(lives != 0){
        if(key == 'w'){//move player up
            if(playerYpos >= 0)
            {
                playerYpos -= 10;
            }
           
        }
        else if(key == 's'){//move player down
            if(playerYpos <= screenHeight)
            {
                playerYpos += 10;
            }
        }
        else if(key == 'a'){//move player left
            if(playerXpos >= 0)
            {
                playerXpos -= 10;    
            }
        }
        else if(key == 'd'){//move player right
            if(playerXpos <= screenWidth)
            {
                playerXpos += 10;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
