/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GRID_VIEW_H__
#define _COMPONENTS_VIEW_GRID_VIEW_H__

#include "cocos2d.h"
#include <memory>
#include <vector>

namespace Components
{
  namespace View
  {
    class GridView: public cocos2d::DrawNode {
    public:
      static GridView* create(size_t width, size_t height, size_t cellSize);

      virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

      bool convert(cocos2d::Touch* touch, size_t& x, size_t& y);
      cocos2d::Vec2 getCenter(size_t x, size_t y);

      inline size_t width() const { return m_width; }
      inline size_t height() const { return m_height; }

      inline size_t cellSize() const { return m_cellSize; }

    private:
      GridView(size_t width, size_t height, size_t cellSize);

    private:
      size_t m_width;
      size_t m_height;
      size_t m_cellSize;


      std::vector<cocos2d::Vec2> m_vertices;
    };
  };
};

#endif // _COMPONENTS_VIEW_GRID_VIEW_H__
