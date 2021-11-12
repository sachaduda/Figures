#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace grechin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double, const double, const point_t&, const double = 0);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(const double) override;
    void rotate(const double) override;
    void setWidth(const double);
    void setHeight(const double);

  private:
    double width_;
    double height_;
    point_t center_;
    double angle_;
  };
}

#endif 
