#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <cassert>

Circle::Circle(const double radius, const point_t& center):
  radius_(radius),
  center_(center)
{
  assert(radius_ > 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void Circle::move(const point_t& movePoint)
{
  center_ = movePoint;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}  
