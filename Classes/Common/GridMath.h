/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMMON_GRID_MATH_H__
#define _COMMON_GRID_MATH_H__

#include "math/Vec2.h"
#include "math/SIAUtils_Point2D.h"
#include <vector>

//#define USE_4_MODEL
#define USE_6_MODEL
//#define USE_8_MODEL

namespace Common
{
  class GridMath {
  public:
    static const double GridCellSize;

#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
    static const size_t MaxCellBuilds = 4;
#elif defined(USE_6_MODEL)
    static const size_t MaxCellBuilds = 3;
#else
#error Defined Model Type
#endif

    static SIAUtils::Position cellPos(cocos2d::Vec2 position);

    static cocos2d::Vec2 center(size_t x, size_t y);
    static cocos2d::Vec2 build(size_t x, size_t y, size_t index);

    static std::vector<cocos2d::Vec2> cellView(size_t x, size_t y, cocos2d::Vec2 translate);

    static const std::vector<SIAUtils::Position>& neighborhood();
    static std::vector<SIAUtils::Position> neighborhood(size_t x, size_t y);
  };
}

#endif // _COMMON_GRID_MATH_H__
