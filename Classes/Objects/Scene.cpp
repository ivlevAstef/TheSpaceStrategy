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

bool Scene::addObject(ObjectPtr pObject) {
  SIA_CHECK_ZERO(pObject.get() == nullptr, WRN);

  auto pEntity = pObject->getComponent<Entity>();
  if (m_cacheArea && pEntity) {
    SIA_CHECK_ZERO(!m_cacheArea->addEntity(pEntity), DBG);
  }

  m_objects.push_back(pObject);
  auto pView = pObject->getComponent<GameView>();
  if (m_cacheGameLayer && pView) {
    m_cacheGameLayer->addGameView(pView);
  }

  return true;
}

void Scene::update() {
  m_cacheArea->update();

  for (ObjectPtr pObject : m_objects) {
    pObject->update();
  }
}