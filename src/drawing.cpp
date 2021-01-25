//include shared
#include "drawing.h"
#include "vex.h"
#include <algorithm>


std::vector<drawing::Button*> drawing::Button::globalButtons;

drawing::Button::Button(int x_, int y_, int width_, int height_, void(*function_pointer_)(), std::string text, color Color) {
  //initialize coordinate values and the function pointer
  x = x_;
  y = y_;
  width = width_;
  height = height_;
  function_pointer = function_pointer_;
  //throw the button onto a static vector to keep track of all the buttons
  //to check if they've been pressed
  globalButtons.push_back(this);
  //draw the button
  Brain.Screen.setPenColor(Color);
  Brain.Screen.setFillColor(Color);
  Brain.Screen.drawRectangle(x, y, width, height);
  if(!text.empty()) {
    Brain.Screen.setPenColor(color(255,255,255));
    drawCenteredText((x + width) / 2, (y + height) / 2, text);
  }
}

drawing::Button::~Button() {
  Brain.Screen.setPenColor(color(0,0,0));
  Brain.Screen.setFillColor(color(0,0,0));
  Brain.Screen.drawRectangle(x, y, width, height);
  globalButtons.erase(remove(globalButtons.begin(), globalButtons.end(), this));
  //must change all the other ids or replace with null to work due to all other elements shifting
  //ugh

}

void drawing::Button::press() {
  int xp = Brain.Screen.xPosition();
  int yp = Brain.Screen.yPosition();
  for(drawing::Button *button : drawing::Button::globalButtons) {
    //check if within x boundry
    if (xp > button->x && xp < button->width) {
      //check if within y boundry
      if(yp > button->y && yp < button->height) {
        //run function that is referenced
        button->function_pointer();
      }
    }
  }
}


void drawing::drawGear(int x, int y, int radius) {
  Brain.Screen.drawCircle(x, y, radius + 10, color(255,255,255));
  Brain.Screen.drawCircle(x, y, radius, color(70,70,70));
}

void drawing::drawCenteredText(int x, int y, std::string text) {
  int centeredX = x - Brain.Screen.getStringWidth(text.c_str())/2;
  int centeredY = y + Brain.Screen.getStringHeight(text.c_str())/2;
  Brain.Screen.printAt(centeredX, centeredY, false, text.c_str());
}

void drawing::drawGridBoxes(int x, int y, int width, int height, int button) {
  for (int j = 0; j < y; j++) {
    for (int k = 0; k < x; k++) {
      
    }
  }
}

//improve 
void drawing::drawLineBoxes(int x, int y, int width, int height, int buttons, direction Direction) {
  if (Direction == horizontal) {
    int interval = (width - y)/buttons;
    for(int i = 0; i < buttons; i++) {
      Brain.Screen.drawRectangle(interval * i, y, interval, height, color(0, 0, 0));
    }
  } else {
    int interval = (height - y)/buttons;
    for(int i = 0; i < buttons; i++) {
      Brain.Screen.drawRectangle(x, interval * i, width, interval, color(0, 0, 0));
    }
  }
}

//upon creating a button it will
//draw the button
//setup callback thing so that when it's pressed it runs a function specified


//callback thing
//upon being pressed perform a binary sort type algorithm to figure out what button was pressed rather than going through an entire list of buttons
//(compare the x, y, w, h to find if the user pressed in region)
//call the function that was specified from a method.
