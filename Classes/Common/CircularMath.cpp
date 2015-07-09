#include "CircularMath.h"
#include "GridMath.h"
#include "SIALogger.h"

using namespace Common;

CircularMath::CircularMath(size_t width, size_t height) {
  m_width = width;
  m_height = height;
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  m_size.width = m_width * GridMath::GridCellSize;
  m_size.height = m_height * GridMath::GridCellSize;
#elif defined(USE_6_MODEL)
  m_size.width = m_width * GridMath::GridCellSize * SQRT3;
  m_size.height = m_height * GridMath::GridCellSize;
#else
#error Defined Model Type
#endif
}


static void normalize(float& value, float size) {
  value += size * (value < 0 ? (1 + (int)(-value / size)) : -((int)(value / size)));
}
static void normalize(int& value, size_t size) {
  value += size * (value < 0 ? (1 + (int)(-value / size)) : -((int)(value / size)));
}

void CircularMath::moveOffset(cocos2d::Vec2 offsetDt) {
  m_offset += offsetDt;
  normalize(m_offset.x, m_size.width);
  normalize(m_offset.y, m_size.height);

  SIATrace("Move offset on (%f,%f) to (%f,%f)", offsetDt.x, offsetDt.y, m_offset.x, m_offset.y);
}

SIAUtils::Point2D<size_t> CircularMath::cellPos(cocos2d::Vec2 position) const {
  position -= m_offset;
  normalize(position.x, m_size.width);
  normalize(position.y, m_size.height);

  return GridMath::cell(position.x, position.y, m_width, m_height);
}

cocos2d::Vec2 CircularMath::center(size_t x, size_t y) const {
  cocos2d::Vec2 center = GridMath::center(x, y);
  center += m_offset;
  normalize(center.x, m_size.width);
  normalize(center.y, m_size.height);

  return center;
}

bool CircularMath::activeZone(size_t x, size_t y) const {
  return true;
}

std::vector<cocos2d::Vec2> CircularMath::cellView(int x, int y) const {
  normalize(x, m_width);
  normalize(y, m_height);
  std::vector<cocos2d::Vec2> res = GridMath::cellView();
  cocos2d::Vec2 centerPos = center(x, y);

  for (size_t i = 0; i < res.size(); i++) {
    res[i] += centerPos;
  }

  return res;
}

cocos2d::Vec2 CircularMath::position(SIAUtils::Point2D<double> pos) const {
  cocos2d::Vec2 res = cocos2d::Vec2(pos.x, pos.y);
  res += m_offset;
  normalize(res.x, m_size.width);
  normalize(res.y, m_size.height);
  return res;
}