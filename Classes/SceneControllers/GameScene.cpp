#include "GameScene.h"
#include "Objects/Building/MainBase.h"

using namespace SceneControllers;
USING_NS_CC;

Scene* GameScene::createScene() {
  auto scene = Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}

bool GameScene::init() {
  if (!Layer::init()) {
    return false;
  }

  m_pScene = Objects::Scene::create();
  this->addChild(m_pScene->getGameLayer());

  scheduleUpdate();

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      auto mainbase = Objects::Building::MainBase::create(i * 10, 4);
      m_pScene->addObject(mainbase);
    }
  }

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      auto mainbase = Objects::Building::MainBase::create(4, i*10);
      m_pScene->addObject(mainbase);
    }
  }

  return true;
}

void GameScene::update(float delta) {
  m_pScene->update();
}