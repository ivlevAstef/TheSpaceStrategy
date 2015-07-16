#include "Object.h"

#include "Models/Entity_Factory.h"
#include "Views/GameView.h"

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

  m_pView = GameView::create(objName);
  SIAFatalAssert(m_pView);

  m_pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIADebug("Select %d", view);
  });
}

void Object::update(SceneInterfacePtr pScene) {
  SIAAssert(pScene);

  SIAAssert(m_pEntity);
  SIAAssert(m_pView);

  ViewPos pos = pScene->viewMath().convert(m_pEntity->pos());
  m_pView->setPosition(pos);

}

Object::~Object() {
}