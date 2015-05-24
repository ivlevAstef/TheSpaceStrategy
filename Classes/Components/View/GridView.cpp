#include "GridView.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GridMath.h"

using namespace Components::View;
using namespace Common;
USING_NS_CC;

GridView* GridView::create(size_t width, size_t height) {
  COMPONENT_ALLOC(GridView)(width, height);
  COMPONENT_INIT(GridView);
}

GridView::GridView(size_t width, size_t height) {
  SIA_CHECK_RET(!init(), ERR);

  m_width = width;
  m_height = height;
}

//TODO:create utils
static double normalizeNumber(double n, double step) {
  if (n < 0) {
    n += step * (1 + (int)(-n / step));
  }
  if (n > step) {
    n -= step * ((int)(n / step));
  }
  return n;
}

void GridView::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
  if ((flags & FLAGS_TRANSFORM_DIRTY) == flags) {
    clear();

    Vec2 pos = getPosition();
    std::vector<cocos2d::Vec2> cellView;

    for (size_t x = 0; x < m_width; x++) {
      for (size_t y = 0; y < m_height; y++) {
        cellView = GridMath::cellView(x, y, -pos);
        //drawPoly(&cellView[0], cellView.size(), true, Color4F(0.1f, 0.05f, 0.3f, 1.0f));
        drawPoly(&cellView[0], cellView.size(), true, Color4F(0.5f, 0.25f, 0.6f, 1.0f));
      }
    }
  }  

  DrawNode::draw(renderer, transform, flags);
}

cocos2d::Vec2 GridView::normalizePosition(cocos2d::Vec2 pos) {
  pos.x = normalizeNumber(pos.x, m_width * GridMath::GridCellSize);
  pos.y = normalizeNumber(pos.y, m_height * GridMath::GridCellSize);
  return pos;
}

bool GridView::convert(cocos2d::Touch* touch, size_t& resX, size_t& resY) {
  SIA_ASSERT(touch);
  Vec2 pos = convertTouchToNodeSpace(touch) + getPosition();
  pos = normalizePosition(pos);

  SIAUtils::Position cellPos = GridMath::cellPos(pos);

  resX = (size_t)cellPos.x;
  resY = (size_t)cellPos.y;
  return true;
}

cocos2d::Vec2 GridView::getCenter(size_t x, size_t y) {
  Vec2 center = GridMath::center(x,y);
  center = center - getPosition();
  center = normalizePosition(center + getContentSize()) - getContentSize();

  return convertToWorldSpace(center);
}