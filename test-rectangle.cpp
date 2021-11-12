#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(rectangle_test)

const double EPSILON = 0.00001;

const double WIDTH = 10.1;
const double HEIGHT = 6.9;
const double AREA = WIDTH * HEIGHT;
const grechin::point_t CENTER = { 7.2, 11.1 };

BOOST_AUTO_TEST_CASE(valid_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, WIDTH);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, HEIGHT);

  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(construct_acute_angle_test)
{
  const double angle = 32;

  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER, angle);

  const double radAngle = angle * M_PI / 180;

  const double newWidth = WIDTH * fabs(cos(radAngle)) + HEIGHT * fabs(sin(radAngle));
  const double newHeight = WIDTH * fabs(sin(radAngle)) + HEIGHT * fabs(cos(radAngle));

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, newWidth, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, newHeight, EPSILON);
}

BOOST_AUTO_TEST_CASE(construct_right_angle_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER, 90);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, WIDTH, EPSILON);
}

BOOST_AUTO_TEST_CASE(construct_negative_angle_test)
{
  const double angle = -57;

  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER, angle);

  const double radAngle = angle * M_PI / 180;

  const double newWidth = WIDTH * fabs(cos(radAngle)) + HEIGHT * fabs(sin(radAngle));
  const double newHeight = WIDTH * fabs(sin(radAngle)) + HEIGHT * fabs(cos(radAngle));

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, newWidth, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, newHeight, EPSILON);
}

BOOST_AUTO_TEST_CASE(move_offset_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const double xMove = 5.3;
  const double yMove = -9.1;

  rectangle.move(xMove, yMove);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, WIDTH);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, HEIGHT);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x + xMove, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y + yMove, EPSILON);
}

BOOST_AUTO_TEST_CASE(move_point_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const grechin::point_t movePoint = { 18.3, -4.1 };

  rectangle.move(movePoint);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);

  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, WIDTH);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, HEIGHT);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, movePoint.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, movePoint.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(scale_increase_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const double coefficient = 3;

  rectangle.scale(coefficient);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(scale_decrease_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const double coefficient = 0.3;

  rectangle.scale(coefficient);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(rotate_acute_angle_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const grechin::rectangle_t recFrame = rectangle.getFrameRect();
  const double recArea = rectangle.getArea();

  const double angle = 32;
  const double radAngle = angle * M_PI / 180;

  const double newWidth = WIDTH * fabs(cos(radAngle)) + HEIGHT * fabs(sin(radAngle));
  const double newHeight = WIDTH * fabs(sin(radAngle)) + HEIGHT * fabs(cos(radAngle));

  rectangle.rotate(angle);

  BOOST_CHECK_CLOSE(rectangle.getArea(), recArea, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, recFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, recFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, newWidth, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, newHeight, EPSILON);
}

BOOST_AUTO_TEST_CASE(rotate_right_angle_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const grechin::rectangle_t recFrame = rectangle.getFrameRect();
  const double recArea = rectangle.getArea();

  rectangle.rotate(90);

  BOOST_CHECK_CLOSE(rectangle.getArea(), recArea, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, recFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, recFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, recFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, recFrame.width, EPSILON);
}

BOOST_AUTO_TEST_CASE(rotate_straight_angle_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const grechin::rectangle_t recFrame = rectangle.getFrameRect();
  const double recArea = rectangle.getArea();

  rectangle.rotate(180);

  BOOST_CHECK_CLOSE(rectangle.getArea(), recArea, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, recFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, recFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, recFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, recFrame.height, EPSILON);
}

BOOST_AUTO_TEST_CASE(rotate_negative_angle_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  const grechin::rectangle_t recFrame = rectangle.getFrameRect();
  const double recArea = rectangle.getArea();

  const double angle = -30;
  const double radAngle = angle * M_PI / 180;
   
  const double newWidth = WIDTH * fabs(cos(radAngle)) + HEIGHT * fabs(sin(radAngle));
  const double newHeight = WIDTH * fabs(sin(radAngle)) + HEIGHT * fabs(cos(radAngle));

  rectangle.rotate(angle);

  BOOST_CHECK_CLOSE(rectangle.getArea(), recArea, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, recFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, recFrame.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, newWidth, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, newHeight, EPSILON);
}

BOOST_AUTO_TEST_CASE(exception_constructor_test)
{
  BOOST_CHECK_THROW(grechin::Rectangle rectangle(0, HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(grechin::Rectangle rectangle(-2, HEIGHT, CENTER), std::invalid_argument);

  BOOST_CHECK_THROW(grechin::Rectangle rectangle(WIDTH, 0, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(grechin::Rectangle rectangle(WIDTH, -2, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_set_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  BOOST_CHECK_THROW(rectangle.setWidth(0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.setWidth(-2), std::invalid_argument);

  BOOST_CHECK_THROW(rectangle.setHeight(0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.setHeight(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_scale_test)
{
  grechin::Rectangle rectangle(WIDTH, HEIGHT, CENTER);

  BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
