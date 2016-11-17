#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

// Find a solution to reduce jitteryness caused by facetacking
// inaccuracies. Blend/'cross dissolve' between frames?

void ofApp::setup(){
	
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    cam.initGrabber(640, 480);
    tracker.setup();
    ofDisableArbTex();
    ofEnableDepthTest();

    // work in Blender to get image wraps working
    model.loadModel("3DModel_wrapped3.dae");
    model.setRotation(0, 0, 0, 0, 0);
    model.setScale(0.9, 0.9, 0.9);
    model.setPosition(50, 50, 0);
    mesh = model.getMesh(0);

    model2.loadModel("3DModel2.3ds");
    model2.setRotation(0, 90, 1, 1, 0);
    model2.setScale(0.9, 0.9, 0.9);
    model2.setPosition(50, 50, 0);
    mesh2 = model2.getMesh(0);

    model3.loadModel("3DModel3.dae");
    model3.setRotation(0, 90, 1, 2, 0);
    model3.setScale(0.9, 0.9, 0.9);
    model3.setPosition(900, 300, 900);
    mesh3 = model3.getMesh(0);

    videoPlayer.loadMovie("video.mp4");
    videoPlayer.play();

    tex.load("pattern_idea.png");
    tex2.load("carrepeatscreenshot4.png");
    //tex3.load("");

    classifier.load("expressions");

    light.enable();
    //light.setPosition(model.getPosition() + ofPoint(0, 0, 1600));
    //light2.enable();
    //light2.setPosition(model2.getPosition() + ofPoint(0, 1600, 0));
    //light3.enable();
    //light3.setPosition(model3.getPosition() + ofPoint(1600, 0, 0));
}

void ofApp::update(){

    cam.update();
    if(cam.isFrameNew()) {

        videoTex.loadData(cam.getPixels());

        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
        }
    }

    videoPlayer.update();
    videoTex2.loadData(videoPlayer.getPixels());

    light.setPosition(easyCam.getPosition());
}

void ofApp::draw(){

    //tracker.draw();
    easyCam.begin();

    //videoPlayer.draw(ofGetWidth()/2, ofGetHeight()/2);

    if(tracker.getFound()) {

      //ofBackground(0, 255, 200);

      // is 'LeftEye' the best solution to determine
      // face movement from left to right?
        ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
        ofVec2f leftCenter = leftEye.getBoundingBox().getCenter();
        float rawLeftEye_x = ofMap(leftCenter.x, 0, 500, 0, 800, true);
        float rawLeftEye_y = ofMap(leftCenter.y, 0, 500, 0, 800, true);
        float rawLrackerScale = ofMap(tracker.getScale(), 0, 8, 0, 400, true);

        leftEye_x = (alpha) * leftEye_x + (1 - alpha) * rawLeftEye_x;
        leftEye_y = (alpha) * leftEye_y + (1 - alpha) * rawLeftEye_y;
        trackerScale = (alpha) * trackerScale + (1 - alpha) * rawLrackerScale;

        //std::cout << << std::endl;

        int n = classifier.size();

        for(int i = 0; i < n; i++){
	  
            if (classifier.getDescription(i) == "smile" &&
                classifier.getProbability(i) > 0.75){

                //ofSetColor(255, 0, 0);
                ofPushMatrix();
                ofScale(trackerScale, trackerScale, trackerScale);
                ofRotate(leftEye_x, 1, 0, 0);
                ofRotate(leftEye_y, 0, 1, 0);
                mesh.drawVertices();
                ofPopMatrix();
            }
            else if (classifier.getDescription(i) == "eyebrows raised" &&
                     classifier.getProbability(i) > 0.9){

                //ofSetColor(255, 0, 0);
                ofPushMatrix();
                ofScale(trackerScale, trackerScale, trackerScale);
                ofRotate(leftEye_x, 1, 0, 0);
                ofRotate(leftEye_y, 0, 1, 0);
                mesh.drawWireframe();
                ofPopMatrix();
            }
            else if (classifier.getDescription(i) == "neutral" &&
                     classifier.getProbability(i) > 0.9){

                //ofSetColor(255, 0, 0);

                ofPushMatrix();

                    ofScale(trackerScale, trackerScale, trackerScale);
                    ofRotate(leftEye_x, 0, 1, 0);
                    ofRotate(leftEye_y, 1, 0, 0);

                         //ofSetColor(254, 100, 200);
                         //tex.bind();
                        videoTex.bind();
                        mesh.drawFaces();
                        videoTex.unbind();
                        //tex.unbind();

                        //ofSetColor(254, 100, 200);
                        mesh.drawFaces();

                ofPopMatrix();
                ofPushMatrix();

                    ofScale(trackerScale - 50, trackerScale - 50, trackerScale - 50);
                    ofRotate(leftEye_x, 1, 0, 0);
                    ofRotate(leftEye_y, 0, 1, 0);

                            tex2.bind();
                            mesh2.drawFaces();
                            tex2.unbind();

                ofPopMatrix();
                ofPushMatrix();

                    ofScale(trackerScale - 50, trackerScale - 50, trackerScale - 50);
                    ofRotate(leftEye_x, 0, 0, 1);
                    ofRotate(leftEye_y, 1, 0, 0);

                            //tex3.bind();
                            videoTex2.bind();
                            mesh3.drawFaces();
                            videoTex2.unbind();
                            //tex3.unbind();

                ofPopMatrix();
            }
            else
            {

                // do somthing...

            }
        }
    }
    else
    {

        //ofBackground(255, 0, 200);

        ofPushMatrix();

            ofScale(200, 200, 200);
            ofRotateX(90 * ofGetElapsedTimef());
            ofRotateY(20 * ofGetElapsedTimef());
            videoTex.bind();
            mesh.drawFaces();
            videoTex.unbind();

        ofPopMatrix();
        ofPushMatrix();

            ofScale(200, 200, 200);
            ofRotateX(20 * ofGetElapsedTimef());
            ofRotateY(90 * ofGetElapsedTimef());
            tex2.bind();
            mesh2.drawFaces();
            tex2.unbind();

        ofPopMatrix();
        ofPushMatrix();

            ofScale(200, 200, 200);
            ofRotateX(10 * ofGetElapsedTimef());
            ofRotateY(20 * ofGetElapsedTimef());
            videoTex2.bind();
            mesh3.drawFaces();
            videoTex2.unbind();

        ofPopMatrix();
    }

    easyCam.end();
}

void ofApp::keyPressed(int key) {

    if(key == 'r') {
        tracker.reset();
        classifier.reset();
    }

    if(key == 'l') {
        classifier.load("expressions");
    }
}
