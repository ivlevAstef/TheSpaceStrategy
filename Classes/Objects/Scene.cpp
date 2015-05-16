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
using namespace Common;

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
  m_cacheGameLayer->modificationBackground(cocos2d::Color3B(150, 150, 200));
  m_cacheGameLayer->setGridView(m_cacheArea->width(), m_cacheArea->height(), m_cacheArea->cellSize());

  using std::placeholders::_1;
  GameTouchEvents::touchBegan += GameTouchEvents::DTouchBegan(this, std::bind(&Scene::touchBegan, this, _1));
}

Scene::~Scene() {
  GameTouchEvents::touchBegan.clean(this);
}

void Scene::touchBegan(Common::GameTouchData data) {
  static size_t lastX = 0;
  static size_t lastY = 0;

  auto pButtonLayer = getComponent<BuildButtonLayer>();

  SIA_ASSERT(nullptr == pButtonLayer);

  addComponent(BuildButtonLayer::create(data.worldCellCenterPos));
  pButtonLayer = getComponent<BuildButtonLayer>();
  SIA_ASSERT(pButtonLayer);

  m_cacheGameLayer->addChild(pButtonLayer, 100);

  pButtonLayer->pick += BuildButtonLayer::DPick(this, [this, data] (std::string pickId) {
    SIA_LOG_INFO("PICK pickID");
    auto newBuild = Objects::Building::BuildFabric::create(pickId, data.x, data.y);
    SIA_CHECK_RET(nullptr == newBuild, WRN);
    addObject(newBuild);
  });

  pButtonLayer->close += BuildButtonLayer::DClose(this, [this] (BuildButtonLayer* layer) {
    SIA_ASSERT(layer);
    eraseComponent(layer);
    m_cacheGameLayer->removeChild(layer);
  }, true);
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

  SIA_LOG_DBG("Added object on scene.");
  return true;
}

void Scene::eraseObject(ObjectPtr pObject) {
  SIA_CHECK_RET(pObject.get() == nullptr, WRN);

  auto pEntity = pObject->getComponent<Entity>();
  if (m_cacheArea && pEntity) {
    m_cacheArea->removeEntity(pEntity);
  }

  auto pView = pObject->getComponent<GameView>();
  if (m_cacheGameLayer && pView) {
    m_cacheGameLayer->eraseGameView(pView);
  }

  m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&pObject] (ObjectPtr& pObj) {
    return pObject.get() == pObj.get();
  }), m_objects.end());

  SIA_LOG_DBG("Removed object from scene.");
}

void Scene::update() {
  m_cacheArea->update();

  for (ObjectPtr pObject : m_objects) {
    pObject->update();
  }
}