#include "ofApp.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxTween.h"
#include "Lyrics.hpp"
#include "Fandango.hpp"

#define W 1009
#define H 748
#define NUM 10
#define FROM 500
#define TO 0
#define DURATION 1000


//font
ofxTrueTypeFontUC Font;
string sampleString;
vector<ofPath> characters;
vector<ofMesh> mesh;
vector<ofMesh> newMesh;
vector<int> ran;
ofPoint center;
Lyrics lyrics;
ofDirectory dir;
vector<string> fonts;

//tween
ofxTween tween;
ofxEasingQuint easing_bounce;
ofxTween transXtween;
ofxTween transYtween;
bool bSwitchFont;
bool bDrawCircle;
Fandango Fandango[NUM];


void ofApp::setup(){
    
    ofHideCursor();
    
    Font.loadFont("Ag.ttf", 64, true, true);
    
    setupMesh();
    
    dir.listDir("");
    for(int i = 0; i < dir.size(); i++){
        fonts.push_back(dir.getName(i));
    }
    
    for (int i = 0; i < NUM; i++) {
        Fandango[i].setup(lyrics.circleLyrics, 200, 200);
    }
}

void ofApp::update(){
    
    if(bDrawCircle){
        for(int i = 0; i < NUM; i++){
            Fandango[i].update(1.5);
        }
    }
    
    if(!bSwitchFont){
        for(int i = 0; i < mesh.size(); i++){
            for(int j = 0; j < mesh[i].getVertices().size(); j++){
                ofVec3f pos = newMesh[i].getVertices()[j] + ran[j];
                ofVec3f endPos = mesh[i].getVertices()[j];
                pos += (endPos - pos) * 0.2;
                newMesh[i].setVertex(j, pos);
            }
        }
    }
    
    if(ofGetFrameNum() % 5 == 0 && bSwitchFont){
        Font.loadFont(fonts[ofRandom(0, fonts.size())], 64, true, true);
        mesh.clear();
        characters = Font.getStringAsPoints(sampleString);         center = ofPoint(Font.stringWidth(sampleString)/2, Font.stringHeight(sampleString)/2);
        
        for(int i = 0; i < characters.size(); i++){
            mesh.push_back(characters[i].getTessellation());
        }
    }
}

void ofApp::draw(){
    
    ofBackgroundGradient( ofColor(1), ofColor(16) );
    
    ofPushMatrix();
    ofTranslate(W/2, H/2);
    if(bDrawCircle){
        for(int i = 0; i < NUM; i++){
            Fandango[i].draw();
        }
    }
    ofTranslate(-center.x, center.y);
    ofTranslate(transXtween.update(), transYtween.update());
    for(int i = 0; i < mesh.size(); i++){
        if(bSwitchFont){
            mesh[i].drawWireframe();
        }else{
            newMesh[i].drawWireframe();
        }
    }
    ofPopMatrix();
    
}

void ofApp::keyPressed(int key){
    
    if(key == 'o'){
        
        transXtween.setParameters(1, easing_bounce, ofxTween::easeOut, ofRandom(-FROM, FROM), ofRandom(-100, 100), DURATION, 0);
        transYtween.setParameters(1, easing_bounce, ofxTween::easeOut, ofRandom(-FROM, FROM), ofRandom(-100, 100), DURATION, 0);
        setupMesh();
    }
    
    if(key == 's'){
        
        bDrawCircle = !bDrawCircle;
    }
    
    if(key == 'x'){
        
        bSwitchFont = !bSwitchFont;
        if(!bSwitchFont){
            setupMesh();
        }
    }
    
    if(key == OF_KEY_RETURN){
        
        setupMesh();
    }
    
    if(key == OF_KEY_LEFT){
        
        transXtween.setParameters(2, easing_bounce, ofxTween::easeOut, -FROM, TO, DURATION, 0);
        setupMesh();
    }
    
    if(key == OF_KEY_RIGHT){
        
        transXtween.setParameters(1, easing_bounce, ofxTween::easeOut, FROM, TO, DURATION, 0);
        setupMesh();
    }
    
}

void ofApp::setupMesh(){
    
    mesh.clear();
    sampleString = lyrics.getNextString();
    characters = Font.getStringAsPoints(sampleString);
    center = ofPoint(Font.stringWidth(sampleString)/2, Font.stringHeight(sampleString)/2);
    
    for(int i = 0; i < characters.size(); i++){
        mesh.push_back(characters[i].getTessellation());
    }
    
    newMesh = mesh;
    
    ran.clear();
    for(int i = 0; i < mesh.size(); i++){
        for(int j = 0; j < mesh[i].getVertices().size(); j++){
            int n = ofRandom(-2, 2);
            ran.push_back(n);
            
            static float pi;
            float rad = ofRandom(300, 500);
            ofVec2f p = ofVec2f(rad * cos(pi), rad * sin(pi));
            newMesh[i].setVertex(j, mesh[i].getVertex(j) + ofVec3f(p.x, p.y, 0));
            pi += 0.01;
        }
    }
}