#include "Scene.h"
#include "Components/Data/Entity.h"
#include "Components/View/GameView.h"
#include "logger/SIAUtils_Logger.h"

using namespace Objects;
using namespace Components::Data;
using namespace Components::View;

ScenePtr Scene::create() {
  return std::make_shared<Scene>();
}

Scene::Scene() {
  addComponent(Area::create());
  m_cacheArea = getComponent<Area>();

  addComponent(GameLayer::create());
  m_cacheGameLayer = getComponent<GameLayer>();

  m_cacheGameLayer->setBackground("background");
  m_cacheGameLayer->modificationBackground(cocos2d::Color3B(50, 50, 100));
}

void Scene::addObject(ObjectPtr pObject) {
  SIA_CHECK_RET(pObject.get() == nullptr, WRN);
  m_objects.push_back(pObject);

  auto pView = pObject->getComponent<GameView>();
  if (m_cacheGameLayer && pView) {
    m_cacheGameLayer->addGameView(pView);
  }

  auto pEntity = pObject->getComponent<Entity>();
  if (m_cacheArea && pEntity) {
    m_cacheArea->addEntity(pEntity);
  }
}

void Scene::update() {
  //m_cacheArea->update();

  for (ObjectPtr pObject : m_objects) {
    pObject->update();
  }
}