/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_SCENE_CONTROLLERS_GAME_SCENE_H__
#define _SIA_THE_SPACE_STRATEGY_SCENE_CONTROLLERS_GAME_SCENE_H__

#include "cocos2d.h"
#include "Objects/Scene.h"

namespace SceneControllers
{
  class GameScene: public cocos2d::Layer {
  public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);

    virtual void update(float dt) override;

  private:
    Objects::ScenePtr m_pScene;

  };
};

#endif // _SIA_THE_SPACE_STRATEGY_SCENE_CONTROLLERS_GAME_SCENE_H__
