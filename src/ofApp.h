#pragma once

#include "ofMain.h"

#define HANDLE_SIZE = 20;

static int currentImageIndex = 0;

class BaseObject{
public:
	ofVec2f trans, scale;
	float rot;
	bool bSelected;
    int handleSize = 20;
};

class Image : public BaseObject{
	public:
	Image();
    void draw();
    void drawCorners();
    ofImage image;
    bool inside(int x, int y);
    bool isCorner(int x, int y);
    bool isLoaded = false;
    bool isSelected = false;
    bool isRotation = false;
    bool isScaling = false;
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
    
        void imageTranslate(int x, int y);
        void imageRotate();
        void imageScale(int x, int y);

		void saveImg();
        void moveUpInOrder();
        void moveDownInOrder();
        void preImageAddingStep();
		void renderSelection(int x, int y);
		void imgerase(Image *currentImage);
        ofVec3f mouse_last;
        bool isCorner;
        bool imageIsSelected;
        bool isDragged;
        bool isRotation;
        bool isScaling;
    
};
