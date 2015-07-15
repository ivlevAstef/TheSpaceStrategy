/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__
#define _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__

#include "SIAEvent.h"
#include "SIAPoint2D.h"

namespace Objects {
  class Scene;
};

namespace Common
{
  typedef SIA::Point2D<double> TouchPos;

  class GameTouchEvents {
  public:
    typedef SIA::Delegate<TouchPos> DTouchBegan;
    static SIA::FriendEvent<Objects::Scene, TouchPos> touchBegan;

    typedef SIA::Delegate<TouchPos> DTouchMoved;
    static SIA::FriendEvent<Objects::Scene, TouchPos> touchMoved;

    typedef SIA::Delegate<TouchPos> DTouchEnded;
    static SIA::FriendEvent<Objects::Scene, TouchPos> touchEnded;

  };
};

#endif // _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__
