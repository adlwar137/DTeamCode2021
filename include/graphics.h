#include "vex.h"

//this is meant to be a complete rewrite of drawing from the ground up
//for the sins i am about to commit please forgive me Bjarne Stroustrup

//TODO line class

namespace graphics {
  class Point {
    public:
      int x;
      int y;
      int z;
      Point(int x = 0, int y = 0, int z = 0); //constructor
      int GetProjectedX(double fov);
      int GetProjectedY(double fov);
      void draw(double fov); //render point
    //override add vector to point
    //override subtract vector from point
    //override subtractpointfrompoint
  };

  class Rectangle {
    public:
      int x;
      int y;
      int z;
      int width;
      int height;
      Rectangle(int x = 0, int y = 0, int z = 0, int width = 0, int height = 0); //constructor
      void draw(double fov);
    private:
      Point points[4];
  };
}