#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofApp");
    ofSetVerticalSync(true);
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    fillColor.set(255, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
}

//--------------------------------------------------------------
void ofApp::draw(){
        int width = ofGetWidth();
    int height = ofGetHeight();
    int xpos = 0;
    player.set(mouseX, mouseY, 50, 50);
    enemy.set(width * 0.25, height * 0.25, 50, 50);
    enemy2.set(width * 0.75, height * 0.75, 50, 50);
    
    ofBackground(255, 255, 255);
    
    ofSetColor(fillColor);
    // for (int i = 100; i < width/2; i += 100) {
    //     ofRect(xpos, height * 0.25, 200, 100);
    //     xpos += 100;
    // }
    // xpos = width;
    // for (int i = width; i >= width/2; i -= 100) {
    //     ofRect(xpos, height * 0.75, 200, 100);
    //     xpos -= 100;
    // }
    // ofTriangle(mouseX, mouseY, mouseX + 50, mouseY + 50, mouseX - 50, mouseY + 50);
    if(player.intersects(enemy) || player.intersects(enemy2)) {
        fillColor.set(0, 255, 0);
    } else {
        fillColor.set(255, 0, 0);
    }
    ofRect(enemy);
    ofRect(enemy2);
    ofRect(player);
    //ofRect()
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
