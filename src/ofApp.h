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
    ofEasyCam easyCam;

    ofLight light;
    ofLight light2;

    ofxAssimpModelLoader model;
    ofxAssimpModelLoader model2;

    ofVboMesh mesh;
    ofVboMesh mesh2;

    ofImage tex;
    ofImage tex2;

    float leftEye_x = 0;
    float leftEye_y = 0;
    float trackerScale = 0;
    float alpha = 0.92;
};
