#pragma once

#include "ofMain.h"

#define HANDLE_SIZE = 20;

static int currentImageIndex = 0;

class BaseObject{
public:
	ofVec2f trans, scale;
	float rot;
	bool bSelected;
};

class Image : public BaseObject{
	public:
	Image();
    void draw();
    void drawCorners();
    ofImage image;
    bool inside(int x, int y);
	bool isLoaded = false;
    bool isSelected = false;
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void dragEvent(ofDragInfo dragInfo);
		vector<Image *> images;
		Image *currentImage;
    
        void imageTranslate();

		void saveImg();
        void moveUpInOrder();
        void moveDownInOrder();
        void preImageAddingStep();
		void renderSelection(int x, int y);
		void imgerase(Image *currentImage);
        ofVec3f mouse_last;
        bool imageIsSelected;
        bool isDragged;
    
};
