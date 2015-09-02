//
//File: ViewMath.h
//Description: Class with Math function for View and convert to Model.
//Author: Ivlev Alexander. Stef
//Created: 27/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_MATH_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_MATH_H__

#include "Models/Common/ModelMath.h"
#include "cocos2d.h"

namespace Common
{
  typedef cocos2d::Vec2 ViewPos;
  typedef cocos2d::Vec2 ViewScale;
  typedef cocos2d::Size ViewSize;

  class ViewMath {
  private:
    #define sCos45 0.70710678118
    #define sSin45 0.70710678118
  public:
    ViewMath() {
      m_windowPos = ViewPos(0, 0);
    }

    ViewPos windowPos() const {
      return m_windowPos;
    }

    ViewSize windowSize() const {
      return m_windowSize;
    }

    ViewPos convert(EntityPos pos) const {
      double x = pos.x * sCos45 - pos.y * sSin45;
      double y = pos.x * sSin45 + pos.y * sCos45;

      return ViewPos(x * scale().x, y * scale().y);
    }

    EntityPos convert(cocos2d::Vec2 pos) const {
      double x = pos.x * sCos45 + pos.y * sSin45;
      double y = - pos.x * sSin45 + pos.y * sCos45;

      return EntityPos(x / scale().x, y / scale().y);
    }

    ViewPos center(ViewPos pos) const {
      return center(convert(pos));
    }

    ViewPos center(EntityPos pos) const {
      return convert(ModelMath::center(ModelMath::cell(pos)));
    }

    ViewScale scale() const {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
      return ViewScale(100, 100);
#else
      return ViewScale(150, 150);
#endif
    }
    
    ViewScale defaultScale() const {
      return ViewScale(100, 100);
    }

    void setWindowPos(ViewPos windowPos) {
      m_windowPos = windowPos;
    }

    void setWindowSize(ViewSize windowSize) {
      m_windowSize = windowSize;
    }

    void moveWindow(ViewPos dtWindowPos) {
      m_windowPos += dtWindowPos;
    }

  private:
    ViewPos m_windowPos;
    ViewSize m_windowSize;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_VIEW_MATH_H__
