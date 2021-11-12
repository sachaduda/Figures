#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

grechin::Circle::Circle(const double radius, const point_t& center):
  radius_(radius),
  center_(center)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}

double grechin::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

double grechin::Circle::getRadius() const
{
  return radius_;
}

grechin::rectangle_t grechin::Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void grechin::Circle::move(const point_t& movePoint)
{
  center_ = movePoint;
}

void grechin::Circle::move(const double xMove, const double yMove)
{
  center_.x += xMove;
  center_.y += yMove;
}

void grechin::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must be > 0");
  }
  radius_ *= coefficient;
}

void grechin::Circle::rotate(const double)
{
}

void grechin::Circle::setRadius(const double radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
  radius_ = radius;
}
