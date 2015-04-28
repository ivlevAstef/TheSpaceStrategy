#include "Scene.h"
#include "Components/View/GameView.h"

using namespace Objects;
using namespace Components::View;

std::shared_ptr<Scene> Scene::create() {
  return std::make_shared<Scene>();
}

Scene::Scene() {
  addComponent(GameLayer::create());
  m_cacheGameLayer = getComponent<GameLayer>();

  m_cacheGameLayer->setBackground("background");
  m_cacheGameLayer->modificationBackground(cocos2d::Color3B(50, 50, 100));
}

void Scene::addObject(ObjectPtr pObject) {
  auto view = pObject->getComponent<GameView>();
  if (m_cacheGameLayer && view) {
    m_cacheGameLayer->addGameView(view);
  }
}