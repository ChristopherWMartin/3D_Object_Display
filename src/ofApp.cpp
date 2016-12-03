#include "ofApp.h"

using namespace ofxCv;

// Animation in background
// human shaped object & mess with
// scales of objects for projection

void ofApp::setup(){
	
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    cam.initGrabber(640, 480);
    tracker.setup();
    ofDisableArbTex();
    ofEnableDepthTest();

    obj_1.setup("1.dae", 0, 0, 0, 0, 0, 0.9, 50, 50, 0);
    obj_2.setup("2.3ds", 0, 90, 1, 1, 0, 0.9, 50, 50, 0);
    obj_3.setup("3.dae", 0, 90, 1, 2, 0, 0.9, 900, 300, 900);
    obj_4.setup("4.dae", 0, 90, 1, 2, 0, 1, 50, 50, 0);

    videoPlayer.loadMovie("VideoTest3.mp4");
    videoPlayer.play();
    videoPlayer2.loadMovie("VideoTest2.mov");
    videoPlayer2.play();

    tex.load("1.png");
    tex2.load("closeupgrass2large.png");

    light.enable();
}

void ofApp::update(){

    cam.update();
    if(cam.isFrameNew()) {

        // Live webcam texture
        videoTex.loadData(cam.getPixels());

        tracker.update(toCv(cam));
    }

    // Texture from loaded mp4 file
    videoPlayer.update();
    videoTex2.loadData(videoPlayer.getPixels());
    videoPlayer2.update();
    videoTex3.loadData(videoPlayer2.getPixels());

    light.setPosition(easyCam.getPosition());
}

void ofApp::draw(){

    ofColor bgColor(151,206,255);
    ofBackground(bgColor);

    easyCam.setDistance(400);
    easyCam.begin();

    videoTex2.draw(-300, -300);

    if(tracker.getFound()) {

        ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
        ofVec2f leftCenter = leftEye.getBoundingBox().getCenter();
        float rawLeftEye_x = ofMap(leftCenter.x, 0, 500, 0, 800, true);
        float rawLeftEye_y = ofMap(leftCenter.y, 0, 500, 0, 800, true);
        float rawLrackerScale = ofMap(tracker.getScale(), 0, 8, 50, 200, true);

        leftEye_x = (alpha) * leftEye_x + (1 - alpha) * rawLeftEye_x;
        leftEye_y = (alpha) * leftEye_y + (1 - alpha) * rawLeftEye_y;
        trackerScale = (alpha) * trackerScale + (1 - alpha) * rawLrackerScale;

        videoTex.bind();
             obj_1.draw(trackerScale,
                        leftEye_x, 0, 1, 0,
                        leftEye_y, 1, 0, 0,
                        0, 0);
        videoTex.unbind();

        tex.bind();
             obj_2.draw((trackerScale - 50),
                        leftEye_x, 1, 0, 0,
                        leftEye_y, 0, 1, 0,
                        0, 0);
        tex.unbind();

        ofPushMatrix();
        ofTranslate(0, 50, 25);
        videoTex2.bind();
             obj_3.draw((trackerScale - 50),
                        leftEye_x, 0, 0, 1,
                        //leftEye_y, 0, 0, 1,
                        leftEye_y, 1, 0, 0,
                        0, 0);
        videoTex2.unbind();
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(50, 25, 0);
        videoTex3.bind();
        //tex2.bind();
             obj_4.draw((trackerScale - 20),
                        leftEye_x, 0, 1, 0,
                        leftEye_y, 0, 0, 1,
                        0, 0);
        videoTex3.unbind();
        //tex2.unbind();
        ofPopMatrix();

    }

    else

    {

        videoTex.bind();
        obj_1.draw(trackerScale,
                   leftEye_x, 0, 1, 0,
                   leftEye_y, 1, 0, 0,
                   90, 20);
        videoTex.unbind();

        tex.bind();
        obj_2.draw(trackerScale,
                   leftEye_x, 1, 0, 0,
                   leftEye_y, 0, 1, 0,
                   20, 90);
        tex.unbind();

        ofPushMatrix();
        ofTranslate(0, 50, 25);
        videoTex2.bind();
             obj_3.draw((trackerScale - 50),
                        leftEye_x, 0, 0, 1,
                        leftEye_y, 1, 0, 0,
                        10, 20);
        videoTex2.unbind();
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(50, 25, 0);
        videoTex3.bind();
        //tex2.bind();
             obj_4.draw((trackerScale - 20),
                        leftEye_x, 0, 1, 0,
                        leftEye_y, 0, 0, 0,
                        5, 10);
        videoTex3.unbind();
        //tex2.unbind();
        ofPopMatrix();
   }

    easyCam.end();
}
