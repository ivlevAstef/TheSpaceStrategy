#include "GameTouchEvents.h"
//#include "Components/View/GameLayer.h"

using namespace Common;

SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> GameTouchEvents::touchBegan;
SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> GameTouchEvents::touchMoved;
SIAUtils::FriendEvent<Components::View::GameLayer, GameTouchData> GameTouchEvents::touchEnded;