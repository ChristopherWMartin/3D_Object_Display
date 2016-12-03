#pragma once

#include "ofMain.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxAssimpModelLoader.h"
#include "obj.h"

class ofApp : public ofBaseApp{

 public:

  void setup();
    void update();
    void draw();

    obj obj_1;
    obj obj_2;
    obj obj_3;
    obj obj_4;

    ofxFaceTrackerThreaded tracker;
    ofEasyCam easyCam;

    ofLight light;

    ofVideoGrabber cam;
    ofVideoPlayer videoPlayer;
    ofVideoPlayer videoPlayer2;

    ofTexture videoTex;
    ofTexture videoTex2;
    ofTexture videoTex3;

    //ofImage tex;
    ofImage tex;
    ofImage tex2;

    float leftEye_x = 0;
    float leftEye_y = 0;
    float trackerScale = 150;
    float alpha = 0.92;

    float p = 0.0;
};
