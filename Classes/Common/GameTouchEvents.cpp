#include "GameTouchEvents.h"

using namespace Common;

SIAUtils::FriendEvent<Objects::Scene, GameTouchData> GameTouchEvents::touchBegan;
SIAUtils::FriendEvent<Objects::Scene, GameTouchData> GameTouchEvents::touchMoved;
SIAUtils::FriendEvent<Objects::Scene, GameTouchData> GameTouchEvents::touchEnded;