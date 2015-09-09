#include "Object.h"

#include "Models/Entity_Factory.h"
#include "Views/GameView.h"

#include "Properties/EnergyState.h"

#include "SIALogger.h"

SIASetModuleName(Object);

using namespace Common;
using namespace Views;
using namespace Models;
using namespace Objects;

Object::Object(std::string objName, Common::EntityPos pos) {
  m_pEntity = Entity::Factory::createBuildByName(objName);
  SIAFatalAssert(m_pEntity);

  m_pEntity->setPos(pos);

  m_pView = GameView::create(objName, m_pEntity);
  m_pView->retain();

  SIAFatalAssert(m_pView);

  m_pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIADebug("Select %d", view);
  });
}

void Object::draw(SceneInterfacePtr pScene) {
  SIAAssert(pScene);

  SIAAssert(m_pEntity);
  SIAAssert(m_pView);

  SIATrace("Object draw.");
  m_pEntity->draw( [&pScene, this] (const Entity& entity, double dt) {
    ViewPos pos = pScene->viewMath().convert(entity.pos());
    ViewScale scale = pScene->viewMath().scale();
    ViewScale defaultscale = pScene->viewMath().defaultScale();
    
    m_pView->setScale(scale.x / defaultscale.x, scale.y / defaultscale.y);
    m_pView->setPosition(pos);

    if (entity.prop().is<Properties::EnergyState>()) {
      auto eState = entity.prop().as<Properties::EnergyState>();

      m_pView->setEnergyState(eState->connected());
      m_pView->setEnergyRange(eState->range() * scale, eState->connected());
    } else {
      m_pView->setEnergyState(true);
      m_pView->setEnergyRange(cocos2d::Vec2::ZERO, false);
    }

  });
}

Object::~Object() {
  m_pView->release();
}