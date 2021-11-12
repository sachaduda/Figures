#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace grechin
{
  class Circle : public Shape
  {
  public:
    Circle(const double, const point_t&);
    double getArea() const override;
    double getRadius() const;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(const double) override;
    void rotate(const double) override;
    void setRadius(const double);

  private:
    double radius_;
    point_t center_;
  };
}

#endif 
