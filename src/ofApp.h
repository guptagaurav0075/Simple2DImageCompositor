//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Gaurav Gupta
//
//

#pragma once

#include "ofMain.h"
#include "Image.h"

class Manip;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void doDelete();
    void renderSelection();
    void processSelection(int x, int y);
    void savePicture();
    bool imageSelected() { return selectedImage > -1;  }
    void undoTransformations();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void moveUpInOrder();
    void moveDownInOrder();
    void shiftImageOnKeys(ofVec2f point);
    void rotateWithKeyboard(int rotDegree);
    void swapImage(int nextIndex);
    Manip		*manip;
    
private:
    bool        altKeyDown;
    bool		ctrlKeyDown;
    bool		shiftKeyDown;
    vector<Image>	images;
    int			    selectedImage;
    
};
