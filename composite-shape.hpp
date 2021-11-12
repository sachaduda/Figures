#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace grechin
{
  struct rectangle_t;
  struct point_t;
  
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape&);
    CompositeShape(CompositeShape&&) noexcept;
    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape&);
    CompositeShape& operator=(CompositeShape&&) noexcept;
    std::shared_ptr<Shape> operator[](const size_t) const;

    double getArea() const override;
    size_t getSize() const;
    rectangle_t getFrameRect() const override;

    void add(const std::shared_ptr<Shape>&);
    void remove(const size_t);

    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(const double) override;
    void rotate(const double) override;
    
  private:
    typedef std::unique_ptr<std::shared_ptr<Shape>[]> ShapeArray;
    size_t size_;
    ShapeArray array_;
  };
}

#endif
