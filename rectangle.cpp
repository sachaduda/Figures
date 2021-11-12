#include "rectangle.hpp"

#include <cassert>

Rectangle::Rectangle(const double width, const double height, const point_t& center):
  width_(width),
  height_(height),
  center_(center)
{
  assert((width_ > 0) && (height_ > 0));
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ width_, height_, center_ };
}

void Rectangle::move(const point_t& movePoint)
{
  center_ = movePoint;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}  
