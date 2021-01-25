#include "vex.h"

//this is meant to be a complete rewrite of drawing from the ground up
//for the sins i am about to commit please forgive me Bjarne Stroustrup

namespace graphics {
  class Point {
    public:
      int x;
      int y;
      int z;
      Point(int x = 0, int y = 0, int z = 0); //constructor
      int GetProjectedX(double d);
      int GetProjectedY(double d);
      void drawPoint(double d); //render point
    //override add vector to point
    //override subtract vector from point
    //override subtractpointfrompoint
  };
}