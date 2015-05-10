#include "Scene.h"
#include "Components/Data/Entity.h"
#include "Components/View/GameView.h"
#include "Components/InterfaceView/BuildButtonLayer.h"
#include "logger/SIAUtils_Logger.h"

#include "Building/BuildFabric.h"

using namespace Objects;
using namespace Components::Data;
using namespace Components::View;
using namespace Components::InterfaceView;

ScenePtr Scene::create() {
  return std::make_shared<Scene>();
}

Scene::Scene() {
  addComponent(Area::create());
  m_cacheArea = getComponent<Area>();
  SIA_ASSERT(m_cacheArea);

  addComponent(GameLayer::create());
  m_cacheGameLayer = getComponent<GameLayer>();
  SIA_ASSERT(m_cacheGameLayer);

  m_cacheGameLayer->setBackground("background");
  m_cacheGameLayer->modificationBackground(cocos2d::Color3B(50, 50, 100));
  m_cacheGameLayer->setGridView(m_cacheArea->width(), m_cacheArea->height(), m_cacheArea->cellSize());

  using std::placeholders::_1;
  using std::placeholders::_2;
  using std::placeholders::_3;
  m_cacheGameLayer->clickCell += GameLayer::DClickCell(std::bind(&Scene::clickCell, this, _1, _2, _3));
}

void Scene::clickCell(size_t x, size_t y, cocos2d::Vec2 pos) {
  static size_t lastX = 0;
  static size_t lastY = 0;

  auto pButtonLayer = getComponent<BuildButtonLayer>();

  if (pButtonLayer) {
    eraseComponent(pButtonLayer);
    m_cacheGameLayer->removeChild(pButtonLayer);

    if (lastX == x && lastY == y) {
      return;
    }
  }

  lastX = x;
  lastY = y;
  addComponent(BuildButtonLayer::create(pos));
  pButtonLayer = getComponent<BuildButtonLayer>();
  SIA_ASSERT(pButtonLayer);

  m_cacheGameLayer->addChild(pButtonLayer, 100);

  pButtonLayer->pick += BuildButtonLayer::DPick([this, x, y] (BuildButtonLayer* layer, std::string pickId) {
    SIA_ASSERT(layer);
    SIA_LOG_INFO("PICK pickID");
    auto newBuild = Objects::Building::BuildFabric::create(pickId, x, y);
    SIA_CHECK_RET(nullptr == newBuild, WRN);
    addObject(newBuild);

    eraseComponent(layer);
    m_cacheGameLayer->removeChild(layer);
  });

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