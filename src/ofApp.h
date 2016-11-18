#pragma once

#include "ofMain.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

 public:

  void setup();
    void update();
    void draw();

    ofVideoGrabber cam;
    ofVideoPlayer videoPlayer;
    ofTexture videoTex;
    ofTexture videoTex2;
    ofxFaceTrackerThreaded tracker;
    ofEasyCam easyCam;

    ofLight light;
    ofLight light2;
    ofLight light3;

    ofxAssimpModelLoader model;
    ofxAssimpModelLoader model2;
    ofxAssimpModelLoader model3;

    ofVboMesh mesh;
    ofVboMesh mesh2;
    ofVboMesh mesh3;

    ofImage tex;
    ofImage tex2;
    ofImage tex3;

    float leftEye_x = 0;
    float leftEye_y = 0;
    float trackerScale = 0;
    float alpha = 0.92;
};
