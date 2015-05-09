/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__
#define _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../Component.h"
#include "event/Event.h"
#include <string>
#include <memory>

namespace Components
{
  namespace InterfaceView
  {
    class BuildButtonLayer: public cocos2d::Node, public Component {
    public:
      DEFINE_COMPONENT(BuildButtonLayer);

      static BuildButtonLayer* create(cocos2d::Vec2 pos);

    public:

      typedef SIAUtils::Delegate<BuildButtonLayer*> DClose;
      SIAUtils::FriendEvent<BuildButtonLayer, BuildButtonLayer*> close;

      typedef SIAUtils::Delegate<std::string> DPick;
      SIAUtils::FriendEvent<BuildButtonLayer, std::string> pick;

    private:
      BuildButtonLayer(cocos2d::Vec2 pos);
    };
  }
}

#endif // _COMPONENTS_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__
