#include "vex.h"
#include <vector>

namespace drawing {
  class Button {
    public:
      //vector holding all the buttons
      static std::vector<Button*> globalButtons;
      //called when the screen is pressed
      static void press();
      //constructor and deconstructor
      Button(int x_, int y_, int width_, int height_, void(*function_pointer_)(), std::string text_, color Color_ = color(128,128,128));
      ~Button();
      //unique id
      //various variables
      int x;
      int y;
      int width;
      int height;
      void(*function_pointer)();
      std::string text;
      color Color;
  };

  //enum declaration
  enum direction{vertical, horizontal};
  enum MenuState{Home, Settings, Test, Games, AutonomousSelection};

  //draw a gear icon
  void drawGear(int x, int y, int radius);
  //write centered text based on the width and height of the text
  void drawCenteredText(int x, int y, std::string text);

  //
  void drawGridBoxes(int x, int y, int width, int height, int buttons);
  void drawLineBoxes(int x, int y, int width, int height, int buttons, direction Direction);
}