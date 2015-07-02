#include "GridView.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GridMath.h"

using namespace Views;
using namespace Common;
USING_NS_CC;

bool GridView::init(size_t width, size_t height) {
  SIA_CHECK_ZERO(!DrawNode::init(), ERR);

  m_width = width;
  m_height = height;
}

void GridView::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
  /*if ((flags & FLAGS_TRANSFORM_DIRTY) == flags) {
    clear();

    std::vector<cocos2d::Vec2> cellView;

    for (int x = 0; x < (int)m_width; x++) {
      for (int y = 0; y < (int)m_height; y++) {
        cellView = m_circularMath->cellView(x, y);
        //drawPoly(&cellView[0], cellView.size(), true, Color4F(0.1f, 0.05f, 0.3f, 1.0f));
        drawPoly(&cellView[0], cellView.size(), true, Color4F(0.5f, 0.25f, 0.6f, 1.0f));
      }
    }
  }  
  */
  DrawNode::draw(renderer, transform, flags);
}

void GridView::update(const Common::ViewMath& viewMath) {
  m_viewMath = viewMath;
}