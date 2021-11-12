#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(circle_test)

const double EPSILON = 0.00001;

const double RADIUS = 3.2;
const double AREA = M_PI * RADIUS * RADIUS;
const grechin::point_t CENTER = { 7.2, 2.4 };

BOOST_AUTO_TEST_CASE(valid_test)
{
  grechin::Circle circle(RADIUS, CENTER);
  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);

  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(move_offset_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const double xMove = -12.8;
  const double yMove = 1.2;

  circle.move(xMove, yMove);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x + xMove, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y + yMove, EPSILON);
}

BOOST_AUTO_TEST_CASE(move_point_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const grechin::point_t movePoint = { -1.8, 11.2 };

  circle.move(movePoint);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, movePoint.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, movePoint.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(scale_increase_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const double coefficient = 2;

  circle.scale(coefficient);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS * coefficient);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS * coefficient, EPSILON);

  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(scale_decrease_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const double coefficient = 0.2;

  circle.scale(coefficient);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS * coefficient);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA * coefficient * coefficient, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS * coefficient, EPSILON);

  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(rotate_positive_angle_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const double angle = 37;

  circle.rotate(angle);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);

  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(rotate_negative_angle_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  const double angle = -37;

  circle.rotate(angle);

  BOOST_CHECK_EQUAL(circle.getRadius(), RADIUS);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);

  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTER.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(exception_constructor_test)
{
  BOOST_CHECK_THROW(grechin::Circle circle(0, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(grechin::Circle circle(-2, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_set_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  BOOST_CHECK_THROW(circle.setRadius(0), std::invalid_argument);
  BOOST_CHECK_THROW(circle.setRadius(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_scale_test)
{
  grechin::Circle circle(RADIUS, CENTER);

  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
