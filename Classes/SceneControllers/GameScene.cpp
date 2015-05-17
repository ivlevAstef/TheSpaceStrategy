#include "GameScene.h"
#include "Objects/Building/BuildFabric.h"

using namespace SceneControllers;
using namespace Objects::Building;
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
      auto mainbase = BuildFabric::create("MainBase", i * 10, 4);
      m_pScene->addObject(mainbase);
      auto pylon = BuildFabric::create("Pylon", i * 10, 4);
      m_pScene->addObject(pylon);
    }
  }

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      auto mainbase = BuildFabric::create("MainBase", 4, i * 10);
      m_pScene->addObject(mainbase);
      auto pylon = BuildFabric::create("Pylon", 4, i * 10);
      m_pScene->addObject(pylon);
    }
  }

  auto getterMineral = BuildFabric::create("GetterMineral", 5, 5);
  m_pScene->addObject(getterMineral);

  for (size_t i = 0; i < 50; i++) {
    int x = rand() % 32;
    int y = rand() % 32;

    auto minerals = BuildFabric::create("Minerals", x, y);
    m_pScene->addObject(minerals);
  }

  return true;
}

void GameScene::update(float delta) {
  m_pScene->update();
}