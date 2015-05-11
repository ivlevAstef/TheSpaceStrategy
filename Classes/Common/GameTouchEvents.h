/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMMON_GAME_TOUCH_EVENTS_H__
#define _COMMON_GAME_TOUCH_EVENTS_H__

#include "event/Event.h"
#include "cocos2d.h"

namespace Components
{
  namespace View
  {
    class GameLayer;
  };
};

namespace Common
{
  struct GameTouchData {
    cocos2d::Vec2 worldPos; ///on game layer position
    cocos2d::Vec2 worldCellCenterPos; ///on game layer position
    size_t x;
    size_t y;
  };

  class GameTouchEvents {
  public:
    typedef SIAUtils::Delegate<GameTouchData> DTouchBegan;
    static SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> touchBegan;

    typedef SIAUtils::Delegate<GameTouchData> DTouchMoved;
    static SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> touchMoved;

    typedef SIAUtils::Delegate<GameTouchData> DTouchEnded;
    static SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> touchEnded;

  };
};

#endif // _COMMON_GAME_TOUCH_EVENTS_H__
