#include "graphics.h"
//Point
//Point Constructor
graphics::Point::Point(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

int graphics::Point::GetProjectedX(double fov) {
  return ceil(this->x * (fov / this->z));
}

int graphics::Point::GetProjectedY(double fov) {
  return ceil(this->x * (fov / this->z));
}

void graphics::Point::draw(double fov) {
  Brain.Screen.drawPixel(this->GetProjectedX(fov), this->GetProjectedY(fov));
}

//Rectangle
graphics::Rectangle::Rectangle(int x, int y, int z, int width, int height) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->width = width;
  this->height = height;

  this->points[0].x = this->x;
  this->points[0].y = this->y;

  this->points[1].x = this->width;
  this->points[1].y = this->y;

  this->points[2].x = this->x;
  this->points[2].y = this->height;

  this->points[3].x = this->width;
  this->points[3].y = this->height;
}

//TODO draw lines inbetween the points
void graphics::Rectangle::draw(double fov) {
  for(int i = 0; i < sizeof(this->points); i++) {
    points[i].draw(fov);
  }
}