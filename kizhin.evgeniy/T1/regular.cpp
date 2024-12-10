#include "regular.hpp"
#include <cassert>
#include <stdexcept>
#include "base-types.hpp"
#include "point_utils.hpp"

kizhin::Regular::Regular(const point_t& p1, const point_t& p2, const point_t& p3)
{
  if (!isRightTriangle(p1, p2, p3)) {
    throw std::invalid_argument("Invalid Triangle Points");
  }
  vertices_[0] = p1;
  vertices_[1] = p2;
  vertices_[2] = p3;
  center_ = vertices_[0];
  computeFrameRect();
}

double kizhin::Regular::getArea() const
{
  return frameRect_.width * frameRect_.height;
}

const kizhin::rectangle_t& kizhin::Regular::getFrameRect() const
{
  return frameRect_;
}

void kizhin::Regular::move(double dx, double dy)
{
  for (point_t& vertex : vertices_) {
    vertex.x += dx;
    vertex.y += dy;
  }
  frameRect_.pos.x += dx;
  frameRect_.pos.y += dy;
}

void kizhin::Regular::move(const point_t& newPos)
{
  const double dx = newPos.x - center_.x;
  const double dy = newPos.y - center_.y;
  move(dx, dy);
}

void kizhin::Regular::scale(double scaleFactor)
{
  assert(scaleFactor > 0);
  for (point_t& vertex : vertices_) {
    vertex.x = center_.x + scaleFactor * (vertex.x - center_.x);
    vertex.y = center_.y + scaleFactor * (vertex.y - center_.y);
  }
  computeFrameRect();
}

void kizhin::Regular::computeFrameRect()
{
  point_t resultP1 { 0, 0 };
  point_t resultP2 { 0, 0 };
  findMaxLine(vertices_[0], vertices_[1], vertices_[2], resultP1, resultP2);
  const double diameter = computeDistance(resultP1, resultP2);
  const point_t circleCenter = { (resultP1.x + resultP2.x) / 2, (resultP1.y + resultP2.y) / 2 };
  frameRect_ = { diameter, diameter, circleCenter };
}

