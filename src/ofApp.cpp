#include "ofApp.h"

Image::Image(){
    trans.x = 0;
    trans.y = 0;
    scale.x = 1.0;
    scale.y = 1.0;
    rot = 0;
    isSelected = false;
    isLoaded = false;
    //  id = currentImageIndex;
    //  currentImageIndex +=1;
    
}
//--------------------------------------------------------------

void Image::draw(){
    ofPushMatrix();
    ofSetVerticalSync(true);
    if(bSelected){
        ofNoFill();
        ofSetColor(0, 255, 255);
        ofSetLineWidth(2);
        ofDrawRectangle(trans.x-2, trans.y-2, image.getWidth()+4, image.getHeight()+4);
    }
    ofSetColor(255, 255, 255);
    image.draw(trans.x,trans.y);
    ofPopMatrix();
}

//--------------------------------------------------------------
bool Image::inside(int xs, int ys){
    if((xs>=trans.x && xs <= trans.x+image.getWidth()) && (ys>=trans.y && ys<=image.getHeight()+trans.y)){
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
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case OF_KEY_ALT:
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
        cout<<"Going to return now"<<endl<<"Image size is :" <<images.size();
        return;
    }
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
    cout<<images.size()<<endl;
}

//--------------------------------------------------------------
void ofApp::renderSelection(int x, int y){
    bool found = false;
    for(int i = images.size()-1; i>=0; i--){
        if(images[i]->inside(x, y) && !found){
            this->currentImage = images[i];
            images.erase(images.begin()+i);
            images.push_back(currentImage);
            this->currentImage->bSelected=true;
            found = true;
        }else{
            images[i]->bSelected = false;
        }
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
        newImage->bSelected = false;
        images.push_back(newImage);
    }
}
