/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"
#include "Common/ViewMath.h"
#include <memory>
#include <vector>

namespace Views
{
  class GridView: public cocos2d::DrawNode {
  public:
    COCOS2D_FUNC2(GridView, size_t, size_t);
    bool init(size_t width, size_t height);

    void update(const Common::ViewMath& viewMath);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

    inline size_t width() const { return m_width; }
    inline size_t height() const { return m_height; }

  private:
    size_t m_width;
    size_t m_height;

    Common::ViewMath m_viewMath;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_VIEW_GRID_VIEW_H__
