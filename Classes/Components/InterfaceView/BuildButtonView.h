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

      static BuildButtonView* create(std::string viewId);

    public:
      BuildButtonView(std::string viewId);

      typedef SIAUtils::Delegate<BuildButtonView*> DClick;

      SIAUtils::FriendEvent<BuildButtonView, BuildButtonView*> click;

    private:
      void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);

    private:
      std::string m_viewId;
      cocos2d::ui::Widget* button;
    };
  }
}

#endif // _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_VIEW_H__
