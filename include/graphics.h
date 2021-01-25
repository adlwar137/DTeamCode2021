#include "vex.h"

//this is meant to be a complete rewrite of drawing from the ground up
//for the sins i am about to commit please forgive me Bjarne Stroustrup

//TODO line class

namespace graphics {
  class Point {
    public:
      Point(int x = 0, int y = 0, int z = 0); //constructor
      int GetProjectedX(double fov);
      int GetProjectedY(double fov);
      void draw(double fov); //render point
      //Getters
      int getX();
      int getY();
      int getZ();
      //Setters
      void setX(int x);
      void setY(int y);
      void setZ(int z);
    private:
      int x;
      int y;
      int z;
    //override add vector to point
    //override subtract vector from point
    //override subtractpointfrompoint
  };

  class Line {
    public:
      Line(int x = 0, int y = 0, int z = 0, int x1 = 0, int y1 = 0, int z1 = 0); //constructor
      void draw(double fov); //render line
      //Getters
      int getX();
      int getY();
      int getZ();
      int getX1();
      int getY1();
      int getZ1();
      Point getP1();
      Point getP2();
      //Setters
      void setX(int x);
      void setY(int y);
      void setZ(int z);
      void setX1(int x1);
      void setY1(int y1);
      void setZ1(int z1);
      void setP1(Point p1);
      void setP2(Point p2);
    private:
      Point p1;
      Point p2;
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