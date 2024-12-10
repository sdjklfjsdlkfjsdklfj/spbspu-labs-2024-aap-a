#ifndef POINT_UTIlS_HPP
#define POINT_UTIlS_HPP

#include "base-types.hpp"

namespace kizhin {
  double computeDistance(const point_t&, const point_t&);
  double computeDistanceSqr(const point_t&, const point_t&);
  bool isRightTriangle(const point_t&, const point_t&, const point_t&);
  bool areCollinear(const point_t&, const point_t&, const point_t&);
  void findMaxLine(const point_t&, const point_t&, const point_t&, point_t&, point_t&);
}

#endif
