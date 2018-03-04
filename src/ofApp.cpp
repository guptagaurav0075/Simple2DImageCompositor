#include "ofApp.h"

Image::Image(){
    trans.x = 0;
    trans.y = 0;
    scale.x = 2.0;
    scale.y = 2.0;
    rot = 0;
    isSelected = false;
    isLoaded = false;
    //  id = currentImageIndex;
    //  currentImageIndex +=1;
    
}
//--------------------------------------------------------------

void Image::draw(){
    ofPushMatrix();
    ofRotate(rot);
    ofScale(scale);
//    ofTranslate(trans);
//    ofSetVerticalSync(true);
    if(bSelected){
        drawCorners();
    }
    ofSetColor(255, 255, 255);
    
    image.draw(trans.x,trans.y);
    ofPopMatrix();
}
//--------------------------------------------------------------
void Image::drawCorners(){
    ofNoFill();
    ofSetColor(0, 255, 255);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x-2, trans.y-2, image.getWidth()+4, image.getHeight()+4);
    
    
    //draw rectangles on the corners of the edges
    int handleSize = 20;
    //left-Upper corner
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x-handleSize/2, trans.y-handleSize/2,handleSize ,handleSize);
    
    //Upper_Left corner
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x-handleSize/2, trans.y-handleSize/2,handleSize ,handleSize);
    
    //Upper_Right corner
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x+image.getWidth()-handleSize/2, trans.y-handleSize/2,handleSize ,handleSize);
    
    //Bottom_Left corner
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x-handleSize/2, trans.y+image.getHeight()-handleSize/2,handleSize ,handleSize);
    
    //Bottom_Right corner
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofDrawRectangle(trans.x+image.getWidth()-handleSize/2, trans.y+image.getHeight()-handleSize/2,handleSize ,handleSize);
    
}
//--------------------------------------------------------------
bool Image::inside(int xs, int ys){
//    if(isCorner(xs, ys)){
//        isScaling = true;
//        return true;
//    }
//    else
    if((xs>=trans.x && xs <= trans.x+image.getWidth()) && (ys>=trans.y && ys<=image.getHeight()+trans.y)){
        return true;
    }
    else if(xs>=trans.x-handleSize/2 && xs<=trans.x-handleSize/2){
        //Check top-left corner
    }
    
    return false;
}//--------------------------------------------------------------
bool Image::isCorner(int xs, int ys){
    //check Top-Left corner
    if((xs>=(trans.x-handleSize/2) && xs<=(trans.x+handleSize/2))&&(ys>=(trans.y-handleSize/2) && ys<=(trans.y+handleSize/2))){
        cout<<"Top Left corner selected"<<endl;
        return true;
    }//Check Top-Right corner
    else if((xs>=(trans.x+image.getWidth()-handleSize/2) && xs<=(trans.x+image.getWidth()+handleSize/2))&&(ys>=(trans.y-handleSize/2) && ys<=(trans.y+handleSize/2))){
        cout<<"Top Right corner Selected"<<endl;
        return true;
    }//Check Bottom-Left corner
    else if((xs>=(trans.x-handleSize/2) && xs<=(trans.x+handleSize/2))&&(ys>=(trans.y+image.getHeight()-handleSize/2) && ys<=(trans.y+image.getHeight()+handleSize/2))){
        cout<<"Bottom-Left corner Selected"<<endl;
        return true;
    }//Check Bottom-Right corner
    else if((xs>=(trans.x+image.getWidth()-handleSize/2) && xs<=(trans.x+image.getWidth()+handleSize/2))&&(ys>=(trans.y+image.getHeight()-handleSize/2) && ys<=(trans.y+image.getHeight()+handleSize/2))){
        cout<<"Bottom-Right corner selected"<<endl;
        return true;
    }
    return false;
}
//--------------------------------------------------------------
void ofApp::setup(){
    currentImage = NULL;
    isDragged = false;
    currentImage = NULL;
    imageIsSelected = false;
    isCorner = false;
    isScaling = false;
    isRotation = false;
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    for(int i=images.size()-1; i>=0; i--){
        delete images[i];
    }
    
}
//--------------------------------------------------------------
void ofApp::saveImg(){
    ofImage snapshot;
    snapshot.grabScreen(0,0, ofGetWidth(), ofGetHeight());
    string str ="snapshot_"+ofToString(ofGetMinutes())+"_"+ofToString(ofGetSeconds())+".jpg";
    snapshot.save(str);
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    ofFill();
    for(int i = 0; i<images.size(); i++){
        images[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_ALT:
            isRotation = true;
            break;
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
        case 'S':
        case 's':
            saveImg();
            break;
        case 'r':
        case 'u':
        case ' ':
            break;
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
            break;
        case OF_KEY_DOWN:
            moveDownInOrder();
            break;
        case OF_KEY_UP:
            moveUpInOrder();
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_ALT:
            isRotation = false;
            break;
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case OF_KEY_CONTROL:
        case OF_KEY_SHIFT:
            break;
        case OF_KEY_ESC:
            ofExit();
            break;
        case ' ':
            break;
            
        default:
            break;
            
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //      cout<<"mouse \t("<<x<<" , "<<y<<" )"<<endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    isDragged = true;
    
    if(images.size()==0 || currentImage == NULL){
//        cout<<"Going to return now"<<endl<<"Image size is :" <<images.size()<<endl;;
        return;
    }
//    if(!isScaling && !isRotation){
//        imageTranslate(x, y);
//    }
//    else if(isScaling && !isRotation){
//        cout<<"Currently Scalling"<<endl;
//        imageScale(x, y);
//    }
    imageTranslate(x, y);
    
}
//--------------------------------------------------------------
void ofApp::imageScale(int x, int y){
    ofPoint mouse_curr = ofPoint(x,y);
    ofVec3f delta = mouse_curr-mouse_last;
    mouse_last = mouse_curr;
    int wid = this->currentImage->image.getWidth();
    int hgt = this->currentImage->image.getHeight();
    cout<<"New Height is "<<hgt<<endl<<"New Wid is "<<wid<<endl;
    this->currentImage->scale += -delta/this->currentImage->image.getWidth()/2;
    this->currentImage->image.resize(wid-delta.x, hgt-delta.y);
    wid = this->currentImage->image.getWidth();
    hgt = this->currentImage->image.getHeight();
    cout<<"New Height is "<<hgt<<endl<<"New Wid is "<<wid<<endl;
    
}
//--------------------------------------------------------------
void ofApp::imageTranslate(int x, int y){
    ofPoint mouse_curr = ofPoint(x,y);
    ofVec3f delta = mouse_curr-mouse_last;
    this->currentImage->trans += delta;
    mouse_last = mouse_curr;
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    currentImage = NULL;
    mouse_last = ofPoint(x,y);
    renderSelection(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(this->currentImage !=NULL && isDragged){
        images.push_back(this->currentImage);
        this->currentImage->bSelected = true;
        this->currentImage = NULL;
    }
    else if(this->currentImage != NULL && !isDragged){
        imageIsSelected = !imageIsSelected;
        cout<<"Image is Selected \t"<<imageIsSelected<<endl;
    }
    isDragged = false;
    isScaling = false;
    cout<<images.size()<<endl;
}

//--------------------------------------------------------------
void ofApp::renderSelection(int x, int y){
    bool found = false;
    int index = -1;
    if(images[images.size()-1]->bSelected && images[images.size()-1]->isCorner(x, y) && !isRotation){
        cout<<"Selected Image for scaling"<<endl;
        this->currentImage = images[images.size()-1];
        this->currentImage->bSelected = true;
        isScaling = true;
        return;
    }
    for(int i = images.size()-1; i>=0; i--){
        if((images[i]->inside(x, y) && !found)){
            this->currentImage = images[i];
            images.erase(images.begin()+i);
            images.push_back(currentImage);
            this->currentImage->bSelected=!this->currentImage->bSelected;
            found = true;
            index = i;
            if(images[i]->isCorner(x, y) && !isRotation){
                cout<<"Selected Image for scaling"<<endl;
                isScaling = true;
                return;
            }
        }
        else{
            images[i]->bSelected = false;
        }
    /**
         if(found){
            if(images[index]->bSelected && images[index]->isCorner(x, y) && !isRotation){
                isScaling = true;
            }
         }
     */
    }
    
}

//--------------------------------------------------------------
void ofApp::moveUpInOrder(){
    if(currentImage!=NULL && images.size()>1){
        for(int i=images.size()-2; i>=0; i--){
            if(images[i]==currentImage){
                images[i] = images[i+1];
                images[i+1] = currentImage;
                currentImage = images[i+1];
                break;
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::moveDownInOrder(){
    if(currentImage!=NULL && images.size()>1){
        cout<<images.size()<<endl;
        for(int i=images.size()-1; i>0; i--){
            cout<<"Current Index :\t"<<i<<endl;
            if(images[i]==currentImage){
                images[i] = images[i-1];
                images[i-1] = currentImage;
                currentImage = images[i-1];
                break;
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    Image *newImage = new Image();
    newImage->trans = dragInfo.position;
    if(newImage->image.load(dragInfo.files[0])==false){
        cout<<"Can't load image : "<<dragInfo.files[0]<<endl;
        delete newImage;
    }
    else{
        preImageAddingStep();
        newImage->bSelected = true;
        images.push_back(newImage);
    }
}
//--------------------------------------------------------------
void ofApp::preImageAddingStep(){
    for (int i=0; i<images.size(); i++) {
        images[i]->bSelected = false;
    }
}
