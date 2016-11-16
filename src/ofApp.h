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

    float leftEye_x = 0;
    float leftEye_y = 0;
    float trackerScale = 0;

    float alpha = 0.92;


};
