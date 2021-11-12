#include "rectangle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include "base-types.hpp" 

grechin::Rectangle::Rectangle(const double width, const double height, const point_t& center, const double angle) :
  width_(width),
  height_(height),
  center_(center),
  angle_(angle)
{
  if (width_ <= 0 || height_ <= 0)
  {
    throw std::invalid_argument("Width and height must be > 0");
  }
}

double grechin::Rectangle::getArea() const
{
  return width_ * height_;
}

grechin::rectangle_t grechin::Rectangle::getFrameRect() const
{
  const double radAngle = angle_ * M_PI / 180;
  const double width = width_ * fabs(cos(radAngle)) + height_ * fabs(sin(radAngle));
  const double height = width_ * fabs(sin(radAngle)) + height_ * fabs(cos(radAngle));
  return rectangle_t{ width, height, center_ };
}

void grechin::Rectangle::move(const point_t& movePoint)
{
  center_ = movePoint;
}

void grechin::Rectangle::move(const double xMove, const double yMove)
{
  center_.x += xMove;
  center_.y += yMove;
}

void grechin::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient mus be > 0");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void grechin::Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ < 0)
  {
    angle_ = 360 + fmod(angle_, 360);
  }
  else
  {
    angle_ = fmod(angle_, 360);
  }
}

void grechin::Rectangle::setWidth(const double width) 
{
  if (width <= 0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
  width_ = width;
}

void grechin::Rectangle::setHeight(const double height) 
{
  if (height <= 0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
  height_ = height;
}
