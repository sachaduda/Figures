#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include <utility>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(composite_shape_test)

const double EPSILON = 0.00001;

const double WIDTH = 10.1;
const double HEIGHT = 6.9;
const double R_AREA = WIDTH * HEIGHT;
const grechin::point_t R_CENTER = { 7.2, 11.1 };

const double RADIUS = 3.2;
const double C_AREA = M_PI * RADIUS * RADIUS;
const grechin::point_t C_CENTER = { 14.6, -12.3 };

struct fixture_t
{
  fixture_t() :
    rect(std::make_shared<grechin::Rectangle>(WIDTH, HEIGHT, R_CENTER)),
    circ(std::make_shared<grechin::Circle>(RADIUS, C_CENTER))
  {
    arr.add(rect);
    arr.add(circ);
  }
  grechin::CompositeShape arr;
  std::shared_ptr<grechin::Rectangle> rect;
  std::shared_ptr<grechin::Circle> circ;
};

BOOST_FIXTURE_TEST_CASE(valid_test, fixture_t)
{
  std::shared_ptr<grechin::CompositeShape> comp = std::make_shared<grechin::CompositeShape>(arr);

  arr.add(comp);

  BOOST_CHECK_EQUAL(rect, arr[0]);
  BOOST_CHECK_EQUAL(circ, arr[1]);
  BOOST_CHECK_EQUAL(comp, arr[2]);

  const double xMax = C_CENTER.x + RADIUS;
  const double xMin = R_CENTER.x - WIDTH / 2;
  const double yMax = C_CENTER.y - RADIUS;
  const double yMin = R_CENTER.y + HEIGHT / 2;

  BOOST_CHECK_EQUAL(arr.getSize(), 3);
  BOOST_CHECK_CLOSE(arr.getArea(), (R_AREA + C_AREA) * 2, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, xMax - xMin, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, yMin - yMax, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, (xMax + xMin) / 2, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, (yMax + yMin) / 2, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(copy_constructor_test, fixture_t)
{
  grechin::CompositeShape arrEmpty;
  grechin::CompositeShape arrEmptyCopy(arrEmpty);

  BOOST_CHECK_EQUAL(arrEmpty.getSize(), arrEmptyCopy.getSize());
  BOOST_CHECK_EQUAL(arrEmpty.getArea(), arrEmptyCopy.getArea());

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().width, arrEmptyCopy.getFrameRect().width);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().height, arrEmptyCopy.getFrameRect().height);

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.x, arrEmptyCopy.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.y, arrEmptyCopy.getFrameRect().pos.y);

  grechin::CompositeShape arrFullCopy(arr);

  BOOST_CHECK_EQUAL(arr.getSize(), arrFullCopy.getSize());
  BOOST_CHECK_EQUAL(arr.getArea(), arrFullCopy.getArea());

  BOOST_CHECK_EQUAL(arr.getFrameRect().width, arrFullCopy.getFrameRect().width);
  BOOST_CHECK_EQUAL(arr.getFrameRect().height, arrFullCopy.getFrameRect().height);

  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.x, arrFullCopy.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.y, arrFullCopy.getFrameRect().pos.y);
}

BOOST_FIXTURE_TEST_CASE(copy_operator_test, fixture_t)
{
  grechin::CompositeShape arrEmpty;
  grechin::CompositeShape arrEmptyCopy;
  arrEmptyCopy = arrEmpty;

  BOOST_CHECK_EQUAL(arrEmpty.getSize(), arrEmptyCopy.getSize());
  BOOST_CHECK_EQUAL(arrEmpty.getArea(), arrEmptyCopy.getArea());

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().width, arrEmptyCopy.getFrameRect().width);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().height, arrEmptyCopy.getFrameRect().height);

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.x, arrEmptyCopy.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.y, arrEmptyCopy.getFrameRect().pos.y);

  grechin::CompositeShape arrFullCopy;
  arrFullCopy = arr;

  BOOST_CHECK_EQUAL(arr.getSize(), arrFullCopy.getSize());
  BOOST_CHECK_EQUAL(arr.getArea(), arrFullCopy.getArea());

  BOOST_CHECK_EQUAL(arr.getFrameRect().width, arrFullCopy.getFrameRect().width);
  BOOST_CHECK_EQUAL(arr.getFrameRect().height, arrFullCopy.getFrameRect().height);

  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.x, arrFullCopy.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.y, arrFullCopy.getFrameRect().pos.y);
}

BOOST_FIXTURE_TEST_CASE(move_constructor_test, fixture_t)
{
  grechin::CompositeShape arrEmpty;
  grechin::CompositeShape arrEmptyMove(std::move(arrEmpty));

  BOOST_CHECK_EQUAL(arrEmpty.getSize(), arrEmptyMove.getSize());
  BOOST_CHECK_EQUAL(arrEmpty.getArea(), arrEmptyMove.getArea());

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().width, arrEmptyMove.getFrameRect().width);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().height, arrEmptyMove.getFrameRect().height);

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.x, arrEmptyMove.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.y, arrEmptyMove.getFrameRect().pos.y);

  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const size_t arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  grechin::CompositeShape arrFullMove(std::move(arr));

  BOOST_CHECK_EQUAL(arrFullMove.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arrFullMove.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().width, arrFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().height, arrFrame.height, EPSILON);

  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(move_operator_test, fixture_t)
{
  grechin::CompositeShape arrEmpty;
  grechin::CompositeShape arrEmptyMove;
  arrEmptyMove = std::move(arrEmpty);

  BOOST_CHECK_EQUAL(arrEmpty.getSize(), arrEmptyMove.getSize());
  BOOST_CHECK_EQUAL(arrEmpty.getArea(), arrEmptyMove.getArea());

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().width, arrEmptyMove.getFrameRect().width);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().height, arrEmptyMove.getFrameRect().height);

  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.x, arrEmptyMove.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(arrEmpty.getFrameRect().pos.y, arrEmptyMove.getFrameRect().pos.y);

  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const size_t arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  grechin::CompositeShape arrFullMove;
  arrFullMove = std::move(arr);

  BOOST_CHECK_EQUAL(arrFullMove.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arrFullMove.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().width, arrFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().height, arrFrame.height, EPSILON);

  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arrFullMove.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(remove_test, fixture_t)
{
  arr.remove(1);

  BOOST_CHECK_EQUAL(arr.getSize(), 1);
  BOOST_CHECK_CLOSE(arr.getArea(), R_AREA, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, HEIGHT, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, R_CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, R_CENTER.y, EPSILON);

  arr.remove(0);

  BOOST_CHECK_EQUAL(arr.getSize(), 0);
  BOOST_CHECK_EQUAL(arr.getArea(), 0);

  BOOST_CHECK_EQUAL(arr.getFrameRect().width, 0);
  BOOST_CHECK_EQUAL(arr.getFrameRect().height, 0);

  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.x, 0);
  BOOST_CHECK_EQUAL(arr.getFrameRect().pos.y, 0);
}

BOOST_FIXTURE_TEST_CASE(move_offset_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const size_t arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  const double xMove = 6.3;
  const double yMove = -3.4;

  arr.move(xMove, yMove);

  BOOST_CHECK_EQUAL(arr.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arr.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.height, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x + xMove, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y + yMove, EPSILON);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, R_CENTER.x + xMove, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, R_CENTER.y + yMove, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, C_CENTER.x + xMove, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, C_CENTER.y + yMove, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(move_point_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const size_t arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  const grechin::point_t movePoint = { 4.5, 8.9 };

  arr.move(movePoint);

  BOOST_CHECK_EQUAL(arr.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arr.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.height, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, movePoint.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, movePoint.y, EPSILON);

  const double rectXPoint = R_CENTER.x + (movePoint.x - arrFrame.pos.x);
  const double rectYPoint = R_CENTER.y + (movePoint.y - arrFrame.pos.y);

  const double circXPoint = C_CENTER.x + (movePoint.x - arrFrame.pos.x);
  const double circYPoint = C_CENTER.y + (movePoint.y - arrFrame.pos.y);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectYPoint, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circYPoint, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(scale_increase_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const double arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  const double coefficient = 4;

  arr.scale(coefficient);

  BOOST_CHECK_EQUAL(arr.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arr.getArea(), arrArea * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.width * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.height * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);

  const double rectXPoint = R_CENTER.x + (R_CENTER.x - arrFrame.pos.x) * (coefficient - 1);
  const double rectYPoint = R_CENTER.y + (R_CENTER.y - arrFrame.pos.y) * (coefficient - 1);

  const double circXPoint = C_CENTER.x + (C_CENTER.x - arrFrame.pos.x) * (coefficient - 1);
  const double circYPoint = C_CENTER.y + (C_CENTER.y - arrFrame.pos.y) * (coefficient - 1);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectYPoint, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circYPoint, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(scale_decrease_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const double arrSize = arr.getSize();
  const double arrArea = arr.getArea();

  const double coefficient = 0.6;

  arr.scale(coefficient);

  BOOST_CHECK_EQUAL(arr.getSize(), arrSize);
  BOOST_CHECK_CLOSE(arr.getArea(), arrArea * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.width * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.height * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);

  const double rectXPoint = R_CENTER.x + (R_CENTER.x - arrFrame.pos.x) * (coefficient - 1);
  const double rectYPoint = R_CENTER.y + (R_CENTER.y - arrFrame.pos.y) * (coefficient - 1);

  const double circXPoint = C_CENTER.x + (C_CENTER.x - arrFrame.pos.x) * (coefficient - 1);
  const double circYPoint = C_CENTER.y + (C_CENTER.y - arrFrame.pos.y) * (coefficient - 1);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectYPoint, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circXPoint, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circYPoint, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(rotate_right_angle_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const double arrArea = arr.getArea();
  const double angle = 90;

  grechin::point_t rectCenter = R_CENTER;
  grechin::point_t circCenter = C_CENTER;

  addition::revolve(rectCenter, arrFrame.pos, angle);
  addition::revolve(circCenter, arrFrame.pos, angle);

  arr.rotate(angle);

  BOOST_CHECK_CLOSE(arr.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.width, EPSILON);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectCenter.y, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circCenter.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(rotate_straight_angle_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const double arrArea = arr.getArea();
  const double angle = 180;

  grechin::point_t rectCenter = R_CENTER;
  grechin::point_t circCenter = C_CENTER;

  addition::revolve(rectCenter, arrFrame.pos, angle);
  addition::revolve(circCenter, arrFrame.pos, angle);

  arr.rotate(angle);

  BOOST_CHECK_CLOSE(arr.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.height, EPSILON);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectCenter.y, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circCenter.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(rotate_negative_angle_test, fixture_t)
{
  const grechin::rectangle_t arrFrame = arr.getFrameRect();
  const double arrArea = arr.getArea();
  const double angle = -90;

  grechin::point_t rectCenter = R_CENTER;
  grechin::point_t circCenter = C_CENTER;

  addition::revolve(rectCenter, arrFrame.pos, angle);
  addition::revolve(circCenter, arrFrame.pos, angle);

  arr.rotate(angle);

  BOOST_CHECK_CLOSE(arr.getArea(), arrArea, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.x, arrFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().pos.y, arrFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(arr.getFrameRect().width, arrFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(arr.getFrameRect().height, arrFrame.width, EPSILON);

  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.x, rectCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[0]->getFrameRect().pos.y, rectCenter.y, EPSILON);

  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.x, circCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(arr[1]->getFrameRect().pos.y, circCenter.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(exception_add_test, fixture_t)
{
  BOOST_CHECK_THROW(arr.add(nullptr), std::invalid_argument);

  std::shared_ptr<grechin::CompositeShape> comp = std::make_shared<grechin::CompositeShape>();

  BOOST_CHECK_THROW(comp->add(comp), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(exception_remove_test, fixture_t)
{
  BOOST_CHECK_THROW(arr.remove(2), std::out_of_range);
  BOOST_CHECK_THROW(arr.remove(-2), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(exception_scale_test, fixture_t)
{
  BOOST_CHECK_THROW(arr.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(arr.scale(-2), std::invalid_argument);

  grechin::CompositeShape arrEmpty;

  BOOST_CHECK_THROW(arrEmpty.scale(2), std::logic_error);
}

BOOST_AUTO_TEST_CASE(exception_move_test)
{
  grechin::CompositeShape arrEmpty;

  BOOST_CHECK_THROW(arrEmpty.move(2, 2), std::logic_error);
  BOOST_CHECK_THROW(arrEmpty.move({ 2,2 }), std::logic_error);
}

BOOST_AUTO_TEST_CASE(exception_rotate_test)
{
  grechin::CompositeShape arrEmpty;

  BOOST_CHECK_THROW(arrEmpty.rotate(30), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
