//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Gaurav Gupta
//
//
//
//

#pragma once
#include "Image.h"

#define HANDLE_SIZE 20

#define MANIP_RECT_ID 99
#define HANDLE_ID_UL 100
#define HANDLE_ID_UR 101
#define HANDLE_ID_LR 102
#define HANDLE_ID_LL 103

//HANDLES FOR NON UNIFORM SCALE
#define HANDLE_ID_UP 104
#define HANDLE_ID_RIGHT 105
#define HANDLE_ID_LEFT 106
#define HANDLE_ID_DOWN 107

typedef enum { ManipDrawNormal, ManipDrawActive, ManipDrawTestSelect } ManipDrawMode;

class Manip : public BaseObject {
    
public:
    Manip();
    void draw(ManipDrawMode mode);
    void scaleUniform(int x, int y);
    void scaleNonUniform(int x, int y);
    void rotate(int x, int y);
    void translate(int x, int y);
    void connect(Image *obj) { this->obj = obj; }
    void disconnect() { this->obj = NULL; }
    void setMouse(int x, int y) { this->mouseLast = ofVec2f(x, y); }
    bool isAUniformHandle(int n);
    bool isANonUniformHandle(int n);
    bool isATranslateBox(int n);
    void setUniformHandle(int n) { uniformHandleIDSelected = n; uniformHandleSelected = true; }
    void setNonUniformHandle(int n) { nonUniformHandleIDSelected = n; nonUniformHandleSelected = true; }
    void setUniformActive(bool);
    void setNonUniformActive(bool);
    void processMouse(int x, int y, int button);
    bool active;
    bool uniformHandleSelected;
    bool isRotationEnabled;
    bool nonUniformHandleSelected;
    ofVec2f getMouseLastLocation();
    
private:
    Image *obj;   // object the  manipulator is connected to
    int handleSize;
    ofVec2f mouseLast;
    int uniformHandleIDSelected;
    int nonUniformHandleIDSelected;
};

