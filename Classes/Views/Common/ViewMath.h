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

  class ViewMath {
  public:
    ViewMath() {
      m_windowPos = ViewPos(0, 0);
    }

    ViewPos windowPos() const {
      return m_windowPos;
    }

    void setWindowPos(ViewPos windowPos) {
      m_windowPos = windowPos;
    }

    void moveWindow(ViewPos dtWindowPos) {
      m_windowPos += dtWindowPos;
    }

    ViewPos convert(EntityPos pos) const {
      return ViewPos(pos.x * scale().x, pos.y * scale().y);
    }

    EntityPos convert(cocos2d::Vec2 pos) const {
      return EntityPos(pos.x / scale().x, pos.y / scale().y);
    }

    ViewPos center(ViewPos pos) const {
      return center(convert(pos));
    }

    ViewPos center(EntityPos pos) const {
      return convert(ModelMath::center(ModelMath::cell(pos)));
    }

    ViewScale scale() const {
      return ViewScale(100, 100);
    }

  private:
    ViewPos m_windowPos;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_VIEW_MATH_H__
