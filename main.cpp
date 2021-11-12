#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

#include <iostream>

void printShapeInfo(const Shape*);

int main()
{
  Circle circle(3.3, { 4.2, 5.6 });
  Shape* shape = &circle;
  std::cout << "***CIRCLE***\n";
  printShapeInfo(shape);

  shape->move(12.3, 9.7);
  std::cout << "Moving to {x+=12.3, y+=9.7}\n";
  printShapeInfo(shape);

  shape->move({ 2.0, 8.9 });
  std::cout << "Moving to {2.0, 8.9}\n";
  printShapeInfo(shape);

  Rectangle rectangle(9.8, 6.7, { 3.4, 5.9 });
  shape = &rectangle;
  std::cout << "***RECTANGLE***\n";
  printShapeInfo(shape);

  shape->move(23.45, 19.89);
  std::cout << "Moving to {x+=23.45, y+=19.89}\n";
  printShapeInfo(shape);

  shape->move({ 11.45, 10.00 });
  std::cout << "Moving to {11.45, 10.00}\n";
  printShapeInfo(shape);

  return 0;
}

void printShapeInfo(const Shape* shape)
{
  rectangle_t frame = shape->getFrameRect();
  std::cout << "Figure's area: " << shape->getArea() << '\n'
  << "Frame's width: " << frame.width << '\n'
  << "Frame's height: " << frame.height << '\n'
  << "Frame's center point {x;y}: {" << frame.pos.x << ';' << frame.pos.y << "}\n\n";
}    
