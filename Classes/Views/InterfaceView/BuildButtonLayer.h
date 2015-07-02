/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__
#define _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__

#include "event/Event.h"

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"
#include <string>
#include <memory>

namespace Views
{
  class BuildButtonLayer: public cocos2d::Node {
  public:
    COCOS2D_FUNC1(BuildButtonLayer, cocos2d::Vec2);
    bool init(cocos2d::Vec2 pos);

    ~BuildButtonLayer();
      
  public:
    typedef SIAUtils::Delegate<std::string> DPick;
    SIAUtils::FriendEvent<BuildButtonLayer, std::string> pick;

    typedef SIAUtils::Delegate<BuildButtonLayer*> DClose;
    SIAUtils::FriendEvent<BuildButtonLayer, BuildButtonLayer*> close;
  };
}

#endif // _SIA_THE_SPACE_STRATEGY_INTERFACE_VIEW_BUILD_BUTTON_LAYER_H__
