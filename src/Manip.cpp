//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Gaurav Gupta
//
//  Manipulator Class - Implementation
//
//  In this example Manipulator class handles following features:
//  1.  Uniform Scaling
//  2.  Non Uniform Scaling
//  3.  Rotation
//
//

#include "Manip.h"

Manip::Manip() {
    obj = NULL;
    active = false;
    handleSize = HANDLE_SIZE;
    uniformHandleSelected = false;
    isRotationEnabled = false;
    nonUniformHandleSelected = false;
    
}

void Manip::draw(ManipDrawMode mode) {
    if (obj == NULL) return;

    //
    // manipulator is drawn in world space for this demo, but probably better to draw in
    // screen space (for 3D) to avoid scaling of handles when camera zooms in/out...KMS
    //
    ofPushMatrix();

    ofTranslate(obj->trans);
    ofRotate(obj->rot);
    ofScale(obj->scale);

    ofNoFill();


    // set colour depending on selection mode
    //
    switch (mode) {
        case ManipDrawNormal:
            ofSetColor(255, 0, 0);
            break;
        case ManipDrawActive:
            ofSetColor(0, 255, 0);
            break;
    }

    // active override
    //
    if (active and !nonUniformHandleSelected and !uniformHandleSelected){
        ofSetColor(255, 255, 255);
    }else if (active and nonUniformHandleSelected and !uniformHandleSelected){
        ofSetColor(255, 0, 255);
    }else if (active and !nonUniformHandleSelected and uniformHandleSelected){
        ofSetColor(55, 55, 55);
    }

    ofSetLineWidth(2);

    float s = handleSize;
    float w = obj->image.getWidth();
    float h = obj->image.getHeight();

    // draw frame
    //
    if (mode == ManipDrawTestSelect) {
        ofFill();
        ofSetColor(0, MANIP_RECT_ID, 0);
        ofDrawRectangle((-w / 2), (-h / 2), w, h);
    }
    else {
        ofNoFill();
        ofDrawRectangle((-w / 2), (-h / 2), w, h);
    }


    // draw handles
    //
    if (mode == ManipDrawTestSelect) {
        ofFill();
        ofSetColor(0, HANDLE_ID_UL, 0);
        ofDrawRectangle((-w / 2) - s / 2, (-h / 2) - s / 2, s, s);
        ofSetColor(0, HANDLE_ID_LL, 0);
        ofDrawRectangle((-w / 2) - s / 2, (h / 2) - s / 2, s, s);
        ofSetColor(0, HANDLE_ID_LR, 0);
        ofDrawRectangle((w / 2) - s / 2, (h / 2) - s / 2, s, s);
        ofSetColor(0, HANDLE_ID_UR, 0);
        ofDrawRectangle((w / 2) - s / 2, (-h / 2) - s / 2, s, s);
        
        ofSetColor(0, HANDLE_ID_UP, 0);
        ofDrawRectangle(-s/2, (-h/2) -s/2,s, s);
        ofSetColor(0, HANDLE_ID_RIGHT, 0);
        ofDrawRectangle(((w/2) -s/2),-s/2,s, s);
        ofSetColor(0, HANDLE_ID_DOWN, 0);
        ofDrawRectangle(-s/2,(h/2)-s/2,s, s);
        ofSetColor(0, HANDLE_ID_LEFT, 0);
        ofDrawRectangle(((-w/2)-s/2),-s/2,s, s);
    }
    else {
        
        ofNoFill();
        ofSetColor(100, 150, 200);
        if(uniformHandleSelected){
            ofSetColor(0, 255, 0);
        }
        ofDrawRectangle((-w / 2) - s / 2, (-h / 2) - s / 2, s, s);
        ofDrawRectangle((-w / 2) - s / 2, (h / 2) - s / 2, s, s);
        ofDrawRectangle((w / 2) - s / 2, (h / 2) - s / 2, s, s);
        ofDrawRectangle((w / 2) - s / 2, (-h / 2) - s / 2, s, s);
        
        ofNoFill();
        ofSetColor(200, 100, 150);
        if(nonUniformHandleSelected)
            ofSetColor(0, 255, 0);
        //left
        ofDrawRectangle(((-w/2)-2*s),-s/2,3*s, s);
        //up
        ofDrawRectangle(-s/2, (-h/2)-2*s, s, 3*s);
        //right
        ofDrawRectangle(((w/2) -s),-s/2,3*s, s);
        //down
        ofDrawRectangle(-s/2,(h/2)-s,s, 3*s);
    }
    ofPopMatrix();
}


//  Process mouse events in the manipulator. In this case, the manipulator
//  is a scale/translate event.
//
void Manip::processMouse(int x, int y, int button) {
    if(isRotationEnabled){
        rotate(x, y);
    }
    else if (uniformHandleSelected)
        scaleUniform(x, y);
    else if(nonUniformHandleSelected)
        scaleNonUniform(x, y);
    else
        translate(x, y);
}

void Manip::scaleNonUniform(int x, int y){
    if (obj == NULL) return;  // guard
    
    ofVec2f mouse = ofVec2f(x, y);
    ofVec2f delta = mouse - mouseLast;
    mouseLast = mouse;
    //non uniform scale
    if(nonUniformHandleSelected){
        switch(nonUniformHandleIDSelected){
         case HANDLE_ID_UP:
             obj->scale.y = obj->scale.y + -delta.y / (obj->image.getWidth() / 2);
             break;
         case HANDLE_ID_DOWN:
             obj->scale.y = obj->scale.y + delta.y / (obj->image.getWidth() / 2);
             break;
         case HANDLE_ID_LEFT:
             obj->scale.x = obj->scale.x + -delta.x / (obj->image.getWidth() / 2);
                break;
         case HANDLE_ID_RIGHT:
             obj->scale.x = obj->scale.x + delta.x / (obj->image.getWidth() / 2);
             break;
        }
     }
}
void Manip::scaleUniform(int x, int y) {
    if (obj == NULL) return;  // guard

    ofVec2f mouse = ofVec2f(x, y);
    ofVec2f delta = mouse - mouseLast;
    mouseLast = mouse;
    
    if(uniformHandleIDSelected){
        switch (uniformHandleIDSelected) {
            case HANDLE_ID_LL:
            case HANDLE_ID_UL:
                obj->scale = obj->scale + -delta.x / (obj->image.getWidth() / 2);
                break;
            case HANDLE_ID_LR:
            case HANDLE_ID_UR:
                obj->scale = obj->scale + delta.x / (obj->image.getWidth() / 2);
                break;
            default:
                break;
        }
    }
}

void Manip::rotate(int x, int y) {
    if(obj == NULL)
        return;
    
    ofVec2f mouse = ofVec2f(x, y);
    ofVec2f delta = mouse - mouseLast;
    float rotation = delta.length();
    
    if(mouse.x<mouseLast.x){//} || mouse.y<mouseLast.y){
        rotation = -rotation;
    }
    
    // store value of where the mouse was last for next entry
    //
    mouseLast = mouse;
    
    // apply Rotation to image (will be translated to this value on next redraw)
    //
    obj->rot += rotation;
}

void Manip::translate(int x, int y) {

    if (obj == NULL) return;   // check that we are connected to something

    ofVec2f mouse = ofVec2f(x, y);
    ofVec2f delta = mouse - mouseLast;

    // store value of where the mouse was last for next entry
    //
    mouseLast = mouse;

    // apply translation to image (will be translated to this value on next redraw)
    //
    obj->trans += delta;
}

void Manip::setUniformActive(bool state) {
    active = state;
    if (!active) uniformHandleSelected = false;
}

void Manip::setNonUniformActive(bool state){
    active = state;
    if(!active)
        nonUniformHandleSelected = false;
    
}

bool Manip::isAUniformHandle(int n) {
    return (n == HANDLE_ID_UL || n == HANDLE_ID_UR ||
            n == HANDLE_ID_LL || n == HANDLE_ID_LR);
}
bool Manip::isANonUniformHandle(int n){
    return (n==HANDLE_ID_UP ||n== HANDLE_ID_DOWN || n==HANDLE_ID_LEFT || n == HANDLE_ID_RIGHT);
}

bool Manip::isATranslateBox(int n) {
    return (n == MANIP_RECT_ID);
}
ofVec2f Manip::getMouseLastLocation(){
    return mouseLast;
}
