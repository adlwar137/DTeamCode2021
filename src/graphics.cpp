#include "graphics.h"

//Point Constructor
graphics::Point::Point(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

int graphics::Point::GetProjectedX(double d) {
  return ceil(this->x * (d / this->z));
}

int graphics::Point::GetProjectedY(double d) {
  return ceil(this->x * (d / this->z));
}

void graphics::Point::drawPoint(double d) {
  Brain.Screen.drawPixel(this->GetProjectedX(d), this->GetProjectedY(d));
}