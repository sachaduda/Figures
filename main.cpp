#include <iostream>
#include <memory>
#include <stdexcept>

#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

void printShapeInfo(const grechin::Shape*);

int main()
{
  grechin::CompositeShape arr;
  grechin::Shape* shape = &arr;

  try
  {
    grechin::Circle circle(3.3, { 4.2, 5.6 });
    std::shared_ptr<grechin::Circle> circ = std::make_shared<grechin::Circle>(circle);

    arr.add(circ);
    std::cout << "ARRAY_CIRCLE\n";
    printShapeInfo(shape);

    shape->move(12.3, 9.7);
    std::cout << "Moving to {x+=12.3, y+=9.7}\n";
    printShapeInfo(shape);

    shape->move({ 2.0, 8.9 });
    std::cout << "Moving to {2.0, 8.9}\n";
    printShapeInfo(shape);

    shape->scale(2);
    std::cout << "Isotropic scaling (radius *= 2)\n";
    printShapeInfo(shape);
  }
  catch (const std::invalid_argument& ex)
  {
    std::cerr << ex.what() << '\n';
    return -1;
  }

  try
  {
    grechin::Rectangle rectangle(9.8, 6.7, { 3.4, 5.9 });
    std::shared_ptr<grechin::Rectangle> rect = std::make_shared<grechin::Rectangle>(rectangle);

    arr.add(rect);
    std::cout << "RECTANGLE\n";
    printShapeInfo(shape);

    shape->move(23.45, 19.89);
    std::cout << "Moving to {x+=23.45, y+=19.89}\n";
    printShapeInfo(shape);

    shape->move({ 11.45, 10.00 });
    std::cout << "Moving to {11.45, 10.00}\n";
    printShapeInfo(shape);

    shape->scale(3);
    std::cout << "Isotropic csaling (width *= 3, height *= 3)\n";
    printShapeInfo(shape);
  }
  catch (const std::invalid_argument& ex)
  {
    std::cerr << ex.what() << '\n';
    return -1;
  }

  return 0;
}

void printShapeInfo(const grechin::Shape* shape)
{
  grechin::rectangle_t frame = shape->getFrameRect();
  std::cout << "Figure's area:" << shape->getArea() << '\n'
      << "Frame's width:" << frame.width << '\n'
      << "Frame's height:" << frame.height << '\n'
      << "Frame's center point:" << '{' << frame.pos.x << ';' << frame.pos.y << '}' << "\n\n";
}
