//
//File: NextFrameEvents.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:54 13/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_NEXT_FRAME_EVENTS_H__
#define _SIA_THE_SPACE_STRATEGY_NEXT_FRAME_EVENTS_H__

#include "event/Event.h"
#include "math/SIAUtils_Point2D.h"

namespace Objects
{
  class Scene;
};

namespace Common
{
  class NextFrameEvents {
  public:
    typedef SIAUtils::Delegate<double> DNextFrame;
    static SIAUtils::FriendEvent<Objects::Scene, double> nextFrame;

  };
};

#endif // _SIA_THE_SPACE_STRATEGY_NEXT_FRAME_EVENTS_H__
