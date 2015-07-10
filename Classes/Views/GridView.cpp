#include "GridView.h"
#include "SIALogger.h"
#include "Common/GridMath.h"

#include "Models/Common/ModelMath.h"

SIASetModuleName(View);

using namespace Views;
using namespace Common;
USING_NS_CC;

bool GridView::init(Models::ConstGridPtr grid) {
  SIACheckRetValue(!DrawNode::init(), false);

  m_pModel = grid;

  SIADebug("Create grid view.");
  return true;
}

void GridView::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
  SIACheckRet(!m_pModel.get());

  if ((flags & FLAGS_TRANSFORM_DIRTY) == flags) {
    clear();

    auto winPos = m_viewMath.windowPos();

    auto winSize = m_viewMath.windowSize();
    auto scale = m_viewMath.scale();

    auto winModelPos = m_viewMath.convert(Vec2(winPos.x - winSize.width * 0.5, winPos.y + winSize.height * 0.5));

    const std::vector<cocos2d::Vec2> zeroCellPoint = {
      Vec2(-scale.x * 0.5f,-scale.y * 0.5f),
      Vec2( scale.x * 0.5f,-scale.y * 0.5f),
      Vec2( scale.x * 0.5f, scale.y * 0.5f),
      Vec2(-scale.x * 0.5f, scale.y * 0.5f)
    };

    std::vector<cocos2d::Vec2> cellPoints(zeroCellPoint.size());

    int bX = -winModelPos.x;
    int bY = -winModelPos.y;
    int size = (winSize.width / scale.x + winSize.height / scale.y) / sqrt(2);

    m_pModel->foreach(bX, bY, size, size, 
      [this, &zeroCellPoint, &cellPoints] (size_t x, size_t y, const Models::Cell& cell) {

      auto posCenter = m_viewMath.convert(ModelMath::center(CellPos(x, y)));

      for (size_t i = 0; i < cellPoints.size(); i++) {
        cellPoints[i] = zeroCellPoint[i] + posCenter;
      }

      Color4F fillColor = Color4F(0.0f, 0.0f, 0.0f, 0.0f);
      if (cell.isGenerator()) {
        fillColor = Color4F(0.5f, 0.0f, 0.5f, 0.5f);
      } else if (cell.isEnergy()) {
        fillColor = Color4F(0.5f, 0.5f, 0.8f, 0.5f);
      } else if (cell.isTransmitter()) {
        fillColor = Color4F(0.0f, 0.8f, 0.0f, 0.5f);
      }

      float borderWidth = 1;
      const Color4F borderColor = Color4F(0.5f, 0.25f, 0.6f, 1.0f);

      drawPolygon(&cellPoints[0], cellPoints.size(), fillColor, borderWidth, borderColor);

      
    });
  }  
  
  DrawNode::draw(renderer, transform, flags);
}

void GridView::update(const Common::ViewMath& viewMath) {
  setPosition(viewMath.windowPos());
  m_viewMath = viewMath;
}