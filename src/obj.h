#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFaceTrackerThreaded.h"

class obj
{

public:

    void setup(string name,
               float rot1, float rot2, float rot3, float rot4, float rot5,
               float scale,
               int pos1, int pos2, int pos3);

    //void update();

    void draw(float trackerScale,
              float leftEye_x, int xrot1, int xrot2, int xrot3,
              float leftEye_y, int xrot4, int xrot5, int xrot6,
              int rotX, int rotY);

    ofxAssimpModelLoader model;
    ofVboMesh mesh;
    ofxFaceTrackerThreaded tracker;
};
