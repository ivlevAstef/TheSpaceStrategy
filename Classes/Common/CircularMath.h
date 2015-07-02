/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_CIRCULAR_MATH_H__
#define _SIA_THE_SPACE_STRATEGY_CIRCULAR_MATH_H__

#include "math/Vec2.h"
#include "math/CCGeometry.h"
#include "math/SIAUtils_Point2D.h"
#include <vector>

namespace Common
{
  class CircularMath {
  public:
    CircularMath(size_t width, size_t height);

    void moveOffset(cocos2d::Vec2 offsetDt);

    inline const cocos2d::Vec2 offset() const { return m_offset; }

    SIAUtils::Point2D<size_t> cellPos(cocos2d::Vec2 position) const;

    cocos2d::Vec2 center(size_t x, size_t y) const;
    bool activeZone(size_t x, size_t y) const;

    std::vector<cocos2d::Vec2> cellView(int x, int y) const;

    cocos2d::Vec2 position(SIAUtils::Point2D<double> pos) const;

  private:
    cocos2d::Vec2 m_offset;

    size_t m_width;
    size_t m_height;

    cocos2d::Size m_size;
  };
} 

#endif // _SIA_THE_SPACE_STRATEGY_CIRCULAR_MATH_H__
