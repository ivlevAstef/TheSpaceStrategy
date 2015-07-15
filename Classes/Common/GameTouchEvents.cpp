#include "GameTouchEvents.h"

using namespace Common;

SIA::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchBegan;
SIA::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchMoved;
SIA::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchEnded;
