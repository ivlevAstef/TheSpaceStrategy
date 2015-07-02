/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__
#define _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__

#include "event/Event.h"
#include "math/SIAUtils_Point2D.h"

namespace Objects {
  class Scene;
};

namespace Common
{
  typedef SIAUtils::Point2D<double> TouchPos;

  class GameTouchEvents {
  public:
    typedef SIAUtils::Delegate<TouchPos> DTouchBegan;
    static SIAUtils::FriendEvent<Objects::Scene, TouchPos> touchBegan;

    typedef SIAUtils::Delegate<TouchPos> DTouchMoved;
    static SIAUtils::FriendEvent<Objects::Scene, TouchPos> touchMoved;

    typedef SIAUtils::Delegate<TouchPos> DTouchEnded;
    static SIAUtils::FriendEvent<Objects::Scene, TouchPos> touchEnded;

  };
};

#endif // _SIA_THE_SPACE_STRATEGY_GAME_TOUCH_EVENTS_H__
