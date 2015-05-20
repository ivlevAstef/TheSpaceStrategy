/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__
#define _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__

#include "cocos2d.h"
#include "../Component.h"
#include "event/Event.h"
#include <string>
#include <memory>

namespace Components
{
  namespace InterfaceView
  {
    class BuildButtonView: public cocos2d::Node, public Component {
    public:
      DEFINE_COMPONENT(BuildButtonView);
      DEFINE_COCOS2DX_COMPONENT

      static BuildButtonView* create(std::string viewId);

      void normal();
      void select();
      void disable();
      bool isSelect();

      bool containsPoint(const cocos2d::Vec2& point) const;

      inline const std::string& viewId() const { return m_viewId; }

    public:
      BuildButtonView(std::string viewId);

    private:
      void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);

    private:
      std::string m_viewId;
      cocos2d::Sprite* m_normal;
      cocos2d::Sprite* m_select;
      cocos2d::Sprite* m_disable;
    };
  }
}

#endif // _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__
