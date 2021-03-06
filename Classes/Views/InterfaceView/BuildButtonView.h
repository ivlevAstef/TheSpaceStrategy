/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__
#define _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__

#include "SIAEvent.h"

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"
#include <string>
#include <memory>

namespace Views
{
  class BuildButtonView: public cocos2d::Node {
  public:
    COCOS2D_FUNC1(BuildButtonView, std::string);
    bool init(std::string viewId);
      

    void normal();
    void select();
    void disable();
    bool isSelect();

    bool containsPoint(const cocos2d::Vec2& point) const;

    inline const std::string& viewId() const { return m_viewId; }

  private:
    void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);

  private:
    std::string m_viewId;
    cocos2d::Sprite* m_normal;
    cocos2d::Sprite* m_select;
    cocos2d::Sprite* m_disable;
  };
}

#endif // _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__
