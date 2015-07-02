#include "GameTouchEvents.h"

using namespace Common;

SIAUtils::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchBegan;
SIAUtils::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchMoved;
SIAUtils::FriendEvent<Objects::Scene, TouchPos> GameTouchEvents::touchEnded;