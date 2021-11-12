#include "base-types.hpp"

#define _USE_MATH_DEFINES

#include <cmath>

void addition::revolve(grechin::point_t& shapeCenter, const grechin::point_t& center, const double angle)
{
  const double radAngle = angle * M_PI / 180;
  const double xTemp = shapeCenter.x - center.x;
  const double yTemp = shapeCenter.y - center.y;
  shapeCenter.x = xTemp * fabs(cos(radAngle)) - yTemp * fabs(sin(radAngle)) + center.x;
  shapeCenter.y = xTemp * fabs(sin(radAngle)) + yTemp * fabs(cos(radAngle)) + center.y;
}

bool addition::isOverlapped(const grechin::rectangle_t& firFrame, const grechin::rectangle_t& secFrame)
{
  const double dx = fabs(firFrame.pos.x - secFrame.pos.x);
  const double dw = fabs(firFrame.width + secFrame.width) / 2;
  const double dy = fabs(firFrame.pos.y - secFrame.pos.y);
  const double dh = fabs(firFrame.height + secFrame.height) / 2;
  return (dx < dw) && (dy < dh);
}
