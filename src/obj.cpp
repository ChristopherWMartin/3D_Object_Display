#include "obj.h"

void obj::setup(string name,
                float rot1, float rot2, float rot3, float rot4, float rot5,
                float scale,
                int pos1, int pos2, int pos3){


    model.loadModel(name);
    model.setRotation(rot1, rot2, rot3, rot4, rot5);
    model.setScale(scale, scale, scale);
    model.setPosition(pos1, pos2, pos3);
    mesh = model.getMesh(0);

}

//void obj::update(){
//}

void obj::draw(float trackerScale,
               float leftEye_x, int xrot1, int xrot2, int xrot3,
               float leftEye_y, int xrot4, int xrot5, int xrot6,
               int rotX, int rotY){


        float time = ofGetElapsedTimef();

        ofPushMatrix();

            ofScale(trackerScale, trackerScale, trackerScale);

            if (rotX > 0 && rotY > 0){
                ofRotateX(rotX * time);
                ofRotateY(rotY * time);
            }

            ofRotate(leftEye_x, xrot1, xrot2, xrot3);
            ofRotate(leftEye_y, xrot4, xrot5, xrot6);

            mesh.drawFaces();

        ofPopMatrix();
}
