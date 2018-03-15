//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Gaurav Gupta
//
//  Class wrapper for an image
//
//  Simple class wrapper to store an ofImage with
//  tranformation attributes (trans, rot and scale)
//
//
//

#pragma once
#include "ofMain.h"

class BaseObject {
public:
    ofVec2f trans, scale;
    float    rot;
    bool    bSelected;
};

class Image : public BaseObject {
    
public:
    Image();
    ofImage image;
    void draw(bool bSelectMode = false, int index = 0);
};



