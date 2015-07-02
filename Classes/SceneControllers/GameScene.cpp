#include "GameScene.h"
#include "Objects/Object.h"

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

  m_pScene = Objects::Scene::create(32, 32);
  this->addChild(m_pScene->getGameLayer());

  scheduleUpdate();

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      auto mainbase = Objects::Object::create("MainBase", Common::EntityPos(i * 10, 4));
      m_pScene->addObject(mainbase);
      auto pylon = Objects::Object::create("Pylon", Common::EntityPos(i * 10, 4));
      m_pScene->addObject(pylon);
    }
  }

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      auto mainbase = Objects::Object::create("MainBase", Common::EntityPos(4, i * 10));
      m_pScene->addObject(mainbase);
      auto pylon = Objects::Object::create("Pylon", Common::EntityPos(4, i * 10));
      m_pScene->addObject(pylon);
    }
  }

  auto getterMineral = Objects::Object::create("MinerMinerals", Common::EntityPos(5, 5));
  m_pScene->addObject(getterMineral);
  m_pScene->eraseObject(getterMineral);

  for (size_t i = 0; i < 500; i++) {
    int x = rand() % 32;
    int y = rand() % 32;

    auto minerals = Objects::Object::create("Minerals", Common::EntityPos(x, y));
    m_pScene->addObject(minerals);
  }

  return true;
}

void GameScene::update(float delta) {
  m_pScene->update(m_pScene);
}