#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

 public:

  void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    ExpressionClassifier classifier;
    ofxAssimpModelLoader model;
    ofxAssimpModelLoader model2;
    ofLight light;
    ofLight light2;
    ofEasyCam easyCam;
    ofVboMesh mesh;
    ofVboMesh mesh2;
    ofImage tex;
};
