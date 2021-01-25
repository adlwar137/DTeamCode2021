#include "graphics.h"
//Point
//Constructor
graphics::Point::Point(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

//get the projected x value to draw to the screen
int graphics::Point::GetProjectedX(double fov) {
  return ceil(this->x * (fov / this->z));
}

//get the projected y value to draw to the screen
int graphics::Point::GetProjectedY(double fov) {
  return ceil(this->x * (fov / this->z));
}

//draw the point to the screen
void graphics::Point::draw(double fov) {
  Brain.Screen.drawPixel(this->GetProjectedX(fov), this->GetProjectedY(fov));
}

//Getters
int graphics::Point::getX() {
  return this->x;
}
int graphics::Point::getY() {
  return this->y;
}
int graphics::Point::getZ() {
  return this->z;
}
//Setters
void graphics::Point::setX(int x) {
  this->x = x;
}
void graphics::Point::setY(int y) {
  this->y = y;
}
void graphics::Point::setZ(int z) {
  this->z = z;
}

//Line
//Constructor
graphics::Line::Line(int x, int y, int z, int x1, int y1, int z1) {
  Point p1(x,y,z);
  Point p2(x1,y1,z1);
}
//Getters
int graphics::Line::getX() {
  return this->p1.getX();
}
int graphics::Line::getY() {
  return this->p1.getY();
}
int graphics::Line::getZ() {
  return this->p1.getZ();
}
int graphics::Line::getX1() {
  return this->p2.getX();
}
int graphics::Line::getY1() {
  return this->p2.getY();
}
int graphics::Line::getZ1() {
  return this->p2.getZ();
}
//Setters

//Rectangle
graphics::Rectangle::Rectangle(int x, int y, int z, int width, int height) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->width = width;
  this->height = height;

  this->points[0].setX(this->x);
  this->points[0].setY(this->y);

  this->points[1].setX(this->width);
  this->points[1].setY(this->y);

  this->points[2].setX(this->x);
  this->points[2].setY(this->height);

  this->points[3].setX(this->width);
  this->points[3].setY(this->height);
}

//TODO draw lines inbetween the points
void graphics::Rectangle::draw(double fov) {
  for(int i = 0; i < sizeof(this->points); i++) {
    points[i].draw(fov);
  }
}