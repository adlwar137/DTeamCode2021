#include "3dgraphics.h"
#include "vex.h"

double getPerspective(double k, double z, double fov) {
  return k * (z / fov);
}

//divide and conquer algorithm for matrix multiplication of matrices of size n^2



/*
//take in a tri object and draw line after running them through a perspective matrix
void drawTriangle(tri triangle, double fov) {
  //temp variables for points after putting them through a perspective matrix
  double x, y
  double x1 = 
}

triangle[0].points.x;
*/
/*
object file parser for faces and vertexes

check if (string before first space) is a vertex
    create a Vec3d object
    store first value before space or linebreak as x
    repeat for y and z
elif face then 
    do the same above but for face
else
    ignore until linebreak
*/