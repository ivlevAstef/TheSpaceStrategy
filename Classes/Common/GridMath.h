/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_GRID_MATH_H__
#define _SIA_THE_SPACE_STRATEGY_GRID_MATH_H__

#include "math/Vec2.h"
#include "math/SIAUtils_Point2D.h"
#include <vector>

//#define USE_4_MODEL
#define USE_6_MODEL
//#define USE_8_MODEL

#ifdef USE_6_MODEL
#define SQRT3 1.732050807568877
#endif

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

    static cocos2d::Vec2 convert(double u, double v);
    static SIAUtils::Point2D<double> convert(cocos2d::Vec2 pos);

    static SIAUtils::Point2D<size_t> cell(double u, double v, size_t width, size_t height);

    static cocos2d::Vec2 center(size_t u, size_t v);
    static cocos2d::Vec2 build(size_t u, size_t v, size_t index);

    static const std::vector<cocos2d::Vec2>& cellView();

    static const std::vector<SIAUtils::Position>& neighborhood();
    static std::vector<SIAUtils::Position> neighborhood(size_t u, size_t b);
  };
}

#endif // _SIA_THE_SPACE_STRATEGY_GRID_MATH_H__
