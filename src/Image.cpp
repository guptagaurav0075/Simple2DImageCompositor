
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

#include "Image.h"

Image::Image()
{
    trans = ofVec3f(0, 0, 0);
    scale = ofVec3f(1, 1, 1);
    rot = 0;              // degrees
    bSelected = false;    // not selected
}

// draw the image.  If testing for selection, using color selection
// just draw a solid rectangle using "index" as a color code for the red
// channel (r, g, b)
//
//
void Image::draw(bool bSelectMode, int index) {
    ofPushMatrix();
    ofTranslate(trans);
    ofRotate(rot);
    ofScale(scale);
    
    if (!bSelectMode) {
        ofSetColor(255, 255, 255, 255);
        image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
    }
    else {
        ofFill();
        ofSetColor(index + 1, 0, 0);
        ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
                        image.getWidth(), image.getHeight());
    }
    ofPopMatrix();
}



