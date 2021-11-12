#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace grechin
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

namespace addition
{
  void revolve(grechin::point_t&, const grechin::point_t&, const double);
  bool isOverlapped(const grechin::rectangle_t&, const grechin::rectangle_t&);
}

#endif 
