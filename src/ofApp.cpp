
#include "ofApp.h"
#include "Manip.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    manip = new Manip();
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    //
    // set when <control> key is held down
    //
    ctrlKeyDown = false;
    altKeyDown = false;
    shiftKeyDown = false;
    selectedImage = -1;      // selection empty;

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofFill();
    
    for (int i = 0; i < images.size(); i++ ) {
        images[i].draw();
    }
    manip->draw(ManipDrawNormal);
}


void ofApp::exit() {
    delete manip;
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'C':
        case 'c':
            break;
            
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            break;
        case 'r':
            break;
        case 's':
        case 'S':
            savePicture();
            break;
        case 'u':
            undoTransformations();
            break;
        case OF_KEY_ALT:
            manip->isRotationEnabled = true;
            altKeyDown = true;
            break;
        case OF_KEY_CONTROL:
        case OF_KEY_COMMAND:
            ctrlKeyDown = true;
            break;
        case OF_KEY_SHIFT:
            shiftKeyDown = true;
            break;
        case OF_KEY_DEL:
            doDelete();
            break;
        case 'd':
        case 'D':
            doDelete();
            break;
        
        case OF_KEY_UP:
            if (ctrlKeyDown) {
                moveUpInOrder();
            }else if(shiftKeyDown){
                ofVec2f point;
                point.set(0,-5);
                shiftImageOnKeys(point);
            }else if(altKeyDown){
                rotateWithKeyboard(1);
            }
            break;
        case OF_KEY_DOWN:
            if(ctrlKeyDown){
                moveDownInOrder();
            }else if(shiftKeyDown){
                ofVec2f point;
                point.set(0,5);
                shiftImageOnKeys(point);
            }else if(altKeyDown){
                rotateWithKeyboard(-1);
            }
            break;
        case OF_KEY_LEFT:
            if(shiftKeyDown){
                ofVec2f point;
                point.set(-5,0);
                shiftImageOnKeys(point);
            }
            break;
        case OF_KEY_RIGHT:
            if(shiftKeyDown){
                ofVec2f point;
                point.set(5,0);
                shiftImageOnKeys(point);
            }
            break;
        
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case OF_KEY_ALT:
            manip->isRotationEnabled = false;
            altKeyDown = false;
            break;
        case OF_KEY_CONTROL:
            ctrlKeyDown = false;
            break;
        case OF_KEY_SHIFT:
            shiftKeyDown = false;
            break;
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
//
// If the manipulator is active, send mouse events to it to process
//
void ofApp::mouseDragged(int x, int y, int button) {
    
    if (manip->active)
        manip->processMouse(x, y, button);
}

//---------------------------------------------------------
//
// delete the selected image
//
void ofApp::doDelete() {
    if (imageSelected())
    {
        manip->disconnect();
        images.erase(images.begin() + selectedImage);
        selectedImage = -1;
    }
}

//  Save the window to an image file on disk
//
void ofApp::savePicture() {
    ofImage snapshot;
    snapshot.grabScreen(0,0, ofGetWidth(), ofGetHeight());
    string str ="snapshot_"+ofToString(ofGetMinutes())+"_"+ofToString(ofGetSeconds())+".jpg";
    snapshot.save(str);
}

//   Undo transformations. Set back to a reasonable default 
// 
void ofApp::undoTransformations() {
    if (imageSelected()) {
        int i = selectedImage;
        images[i].scale = ofVec2f(1, 1);
        images[i].trans = ofVec2f(0, 0);
        images[i].rot = 0;
    }
}

//--------------------------------------------------------------
//
//  Mouse is pressed down, test to see what objects are selected
//
void ofApp::mousePressed(int x, int y, int button){
    renderSelection();
    processSelection(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    manip->setUniformActive(false);
    manip->setNonUniformActive(false);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
//
// Simple file drag and drop implementation.  Drop the image
// under the 
//
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
    Image imageObj;
    
    if (imageObj.image.load(dragInfo.files[0]) == true)
    {
        // disconnect manipulator (if connected)
        //
        manip->disconnect();
        
        // translate image to drop location
        //
        imageObj.trans = ofVec3f(dragInfo.position.x, dragInfo.position.y);
        
        // save image on stack, select it and connect manipulator
        //
        imageObj.bSelected = true;
        images.push_back(imageObj);
        selectedImage = images.size() - 1;
        manip->connect(&images[selectedImage]);
    }
    else {
        cout << "Can't load image: " << dragInfo.files[0] << endl;
    }
}

//
// Render for the purposes of selection hit testing.  In this case
// we use the color method. We render echo object as a different
// value of r,g,b.  We then compare the pixel under the mouse. The
// value is the index into the image list;
//
void ofApp::renderSelection() {
    
    ofBackground(0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //
    // check for any images selected; the color index
    // we use is simple the index of the image in the vector
    //
    for (int i = 0; i < images.size(); i++) {
        images[i].draw(true, i);
    }
    
    //
    // check for manipulator handles selected
    //
    manip->draw(ManipDrawTestSelect);
    
    
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void ofApp::processSelection(int x, int y) {
    unsigned char res[4];
    GLint viewport[4];
    
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
    
    // check if manipulator to see which part of it is selected
    // and set state.
    //
    if (manip->isAUniformHandle(res[1])) {
        manip->setUniformActive(true);
        manip->setUniformHandle(res[1]);
        manip->setMouse(x, y);
        //        cout << "handle: " << res[1] << endl;
        return;
    }
    else if(manip->isANonUniformHandle(res[1])){
        manip->setNonUniformActive(true);
        manip->setNonUniformHandle(res[1]);
        manip->setMouse(x, y);
        return;
    }
    else if (manip->isATranslateBox(res[1])) {
        //        manip->setUniformActive(true);
        manip->active = true;
        manip->setMouse(x, y);
        return;
    }
    
    // Manipulator not selected, disconnect
    //
    if (imageSelected()) {
        images[selectedImage].bSelected = false;
        selectedImage = -1;
        manip->disconnect();
    }
    
    if (res[0] > 0 && res[0] <= images.size()) {
        int id = res[0] - 1;
        Image img = images[id];
        img.bSelected = true;
        
        // move selected image to end of list
        //
        images.erase(images.begin() + id );
        images.push_back(img);
        selectedImage = images.size() - 1;
        
        // connect manipulator
        //
        manip->connect(&images[selectedImage]);
    }
}
//TODO: shift image based on the arrow keys pressed
void ofApp::shiftImageOnKeys(ofVec2f point){
    //Key Pressed Description
    //    1 for Up
    //    2 for Down
    //    3 for Left
    //    4 for Right
    int size = images.size();
    if(selectedImage>-1 and !ctrlKeyDown and shiftKeyDown and size>0){
        images[selectedImage].trans +=point;
        manip->connect(&images[selectedImage]);
    }
    
}

//TODO: Implement level ordering based on the down key pressed
void ofApp::moveDownInOrder(){
    int size = images.size();
    if(selectedImage>-1 and size>1 and ctrlKeyDown and !shiftKeyDown){
        int nextImage = (size+selectedImage-1)%size;
        swapImage(nextImage);
    }
}
//Implemented level ordering based on the up key pressed

void ofApp::moveUpInOrder(){
    int size = images.size();
    if(selectedImage>-1 and size>1 and ctrlKeyDown and !shiftKeyDown){
        int nextImage = (selectedImage+1)%size;
        swapImage(nextImage);
    }
}

//swaps the image with the next image
// function is used with MoveUpInOrder and MoveDownInOrder
void ofApp::swapImage(int nextIndex){
    images[selectedImage].bSelected = false;
    Image currentImage = images[selectedImage];
    images[selectedImage] = images[nextIndex];
    images[nextIndex] = currentImage;
    //    images[nextIndex].bSelected = true;
    selectedImage = nextIndex;
    images[selectedImage].bSelected = true;
    manip->connect(&images[selectedImage]);
    //images.erase(images.begin()+selectedImage);
}

//Rotate with the help of keyboard
void ofApp::rotateWithKeyboard(int rotDegree){
    if(selectedImage>-1 && images.size()>0){
        images[selectedImage].rot +=rotDegree;
    }
}
