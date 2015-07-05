/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"
#include "Common/ViewMath.h"
#include "Models/Grid.h"
#include <memory>
#include <vector>

namespace Views
{
  class GridView: public cocos2d::DrawNode {
  public:
    COCOS2D_FUNC1(GridView, Models::ConstGridPtr);
    bool init(Models::ConstGridPtr);

    void update(const Common::ViewMath& viewMath);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

  private:
    Models::ConstGridPtr m_pModel;

    Common::ViewMath m_viewMath;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__
