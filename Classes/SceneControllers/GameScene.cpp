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

  auto mainbase = Objects::Building::MainBase::create();
  m_pScene->addObject(mainbase);

  return true;
}

void GameScene::update(float delta) {
  m_pScene->update();
}