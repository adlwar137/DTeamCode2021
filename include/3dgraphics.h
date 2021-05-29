#include "vex.h"

struct vec3d {
  public:
    int x, y, z;
};

struct tri {
  public:
    vec3d points[3];
};