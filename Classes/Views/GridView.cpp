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

#define SQRT2 1.414213562373095
    double halfScale = (scale.x + scale.y) / (2.0 * 2.0);
    double octaEdge = 2.0 * halfScale / (SQRT2 + 1.0);
    double octaB = 2.0 * halfScale / (SQRT2 + 2.0);

    const std::vector<cocos2d::Vec2> zeroCellPoint = {
      Vec2(-halfScale, octaB - halfScale),
      Vec2(-halfScale, octaB + octaEdge - halfScale),
      Vec2(octaB - halfScale, halfScale),
      Vec2(octaB + octaEdge - halfScale, halfScale),
      Vec2(halfScale, octaB + octaEdge - halfScale),
      Vec2(halfScale, octaB - halfScale),
      Vec2(octaB + octaEdge - halfScale, -halfScale),
      Vec2(octaB - halfScale, -halfScale)
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