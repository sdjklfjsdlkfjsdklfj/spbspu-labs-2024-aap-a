#include "point_utils.hpp"
#include <cmath>
#include <limits>

double kizhin::computeDistanceSqr(const point_t& p1, const point_t& p2)
{
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return dx * dx + dy * dy;
}

double kizhin::computeDistance(const point_t& p1, const point_t& p2)
{
  double distanceSqr = computeDistanceSqr(p1, p2);
  return std::sqrt(distanceSqr);
}

bool kizhin::isRightTriangle(const point_t& p1, const point_t& p2, const point_t& p3)
{
  if (areCollinear(p1, p2, p3)) {
    return false;
  }
  const double d1 = computeDistanceSqr(p1, p2);
  const double d2 = computeDistanceSqr(p2, p3);
  const double d3 = computeDistanceSqr(p3, p1);
  constexpr double epsilon = std::numeric_limits< double >::epsilon();
  const bool d1IsHypotenuse = std::abs(d1 - (d2 + d3)) < epsilon;
  const bool d2IsHypotenuse = std::abs(d2 - (d1 + d3)) < epsilon;
  const bool d3IsHypotenuse = std::abs(d3 - (d1 + d2)) < epsilon;
  return d1IsHypotenuse || d2IsHypotenuse || d3IsHypotenuse;
}

bool kizhin::areCollinear(const point_t& p1, const point_t& p2, const point_t& p3)
{
  const double leftProduct = (p3.x - p1.x) * (p2.y - p1.y);
  const double rigthProduct = (p2.x - p1.x) * (p3.y - p1.y);
  return std::abs(leftProduct - rigthProduct) < std::numeric_limits< double >::epsilon();
}

void kizhin::findMaxLine(
    const point_t& p1, const point_t& p2, const point_t& p3, point_t& start, point_t& end)
{
  double d1 = computeDistance(p1, p2);
  double d2 = computeDistance(p2, p3);
  double d3 = computeDistance(p3, p1);
  if (d1 > d2 && d1 > d3) {
    start = p1;
    end = p2;
  } else if (d2 > d1 && d2 > d3) {
    start = p2;
    end = p3;
  } else {
    start = p3;
    end = p1;
  }
}
