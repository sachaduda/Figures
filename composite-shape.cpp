#include "composite-shape.hpp"

#include <memory>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include "base-types.hpp"

grechin::CompositeShape::CompositeShape() :
  size_(0),
  array_(nullptr)
{}

grechin::CompositeShape::CompositeShape(const CompositeShape& shape) : 
  size_(shape.size_),
  array_(nullptr)
{
  if (size_ != 0)
  {
    array_ = ShapeArray(new std::shared_ptr<Shape>[size_]);
    for (size_t i = 0; i < size_; i++)
    {
      array_[i] = shape.array_[i];
    }
  }
}

grechin::CompositeShape::CompositeShape(CompositeShape&& shape) noexcept :
  size_(shape.size_), 
  array_(std::move(shape.array_))
{
  if (size_ != 0)
  {
    shape.size_ = 0;
  }
}

grechin::CompositeShape& grechin::CompositeShape::operator=(const CompositeShape& shape)
{
  if (this != &shape)
  {
    if (shape.size_ != 0)
    {
      ShapeArray temp(new std::shared_ptr<Shape>[shape.size_]);
      for (size_t i = 0; i < shape.size_; i++)
      {
        temp[i] = shape.array_[i];
      }
      size_ = shape.size_;
      array_ = std::move(temp);
    }
    else
    {
      size_ = 0;
      array_ = nullptr;
    }
  }
  return *this;
}

grechin::CompositeShape& grechin::CompositeShape::operator=(CompositeShape&& shape) noexcept
{
  if (this != &shape)
  {
    if (shape.size_ != 0)
    {
      size_ = shape.size_;
      shape.size_ = 0;
      array_ = std::move(shape.array_);
    }
    else
    {
      size_ = 0;
      array_ = nullptr;
    }
  }
  return *this;
}

std::shared_ptr<grechin::Shape> grechin::CompositeShape::operator[](const size_t number) const
{
  if (number >= size_)
  {
    throw std::out_of_range("Out of range");
  }
  return array_[number];
}

double grechin::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }
  return area;
}

size_t grechin::CompositeShape::getSize() const
{
  return size_;
}

grechin::rectangle_t grechin::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return { 0, 0, {0, 0} };
  }

  rectangle_t frame = array_[0]->getFrameRect();
  double xMax = frame.pos.x + frame.width / 2;
  double yMax = frame.pos.y + frame.height / 2;
  double xMin = frame.pos.x - frame.width / 2;
  double yMin = frame.pos.y - frame.height / 2;

  for (size_t i = 1; i < size_; i++)
  {
    frame = array_[i]->getFrameRect();
    xMax = std::max(xMax, frame.pos.x + frame.width / 2);
    yMax = std::max(yMax, frame.pos.y + frame.height / 2);
    xMin = std::min(xMin, frame.pos.x - frame.width / 2);
    yMin = std::min(yMin, frame.pos.y - frame.height / 2);
  }
  return rectangle_t{ xMax - xMin, yMax - yMin, { (xMax + xMin) / 2, (yMax + yMin) / 2 } };
}

void grechin::CompositeShape::add(const std::shared_ptr<Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape must not be nullptr");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("Shape must not be self adding");
  }

  ShapeArray temp(new std::shared_ptr<Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    temp[i] = array_[i];
  }
  temp[size_] = shape;
  size_++;
  array_ = std::move(temp);
}

void grechin::CompositeShape::remove(const size_t number)
{
  if (number >= size_)
  {
    throw std::out_of_range("Out of range");
  }

  for (size_t i = number; i < size_ - 1; i++)
  {
    array_[i] = array_[i + 1];
  }
  size_--;
  array_[size_].reset();
}

void grechin::CompositeShape::move(const point_t& movePoint)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }

  const point_t center = getFrameRect().pos;
  move(movePoint.x - center.x, movePoint.y - center.y);
}

void grechin::CompositeShape::move(const double xMove, const double yMove)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }

  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(xMove, yMove);
  }
}

void grechin::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must be > 0");
  }
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }

  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->scale(coefficient);
    const double xMove = (array_[i]->getFrameRect().pos.x - center.x) * (coefficient - 1);
    const double yMove = (array_[i]->getFrameRect().pos.y - center.y) * (coefficient - 1);
    array_[i]->move(xMove, yMove);
  }
}

void grechin::CompositeShape::rotate(const double angle)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }

  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->rotate(angle);
    point_t shapeCenter = array_[i]->getFrameRect().pos;
    addition::revolve(shapeCenter, center, angle);
    array_[i]->move(shapeCenter);
  }
}
