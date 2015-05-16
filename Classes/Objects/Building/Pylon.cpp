#include "Pylon.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<Pylon> Pylon::create(int x, int y) {
  return std::make_shared<Pylon>(x, y);
}

Pylon::Pylon(int x, int y) {
  auto pView = GameView::create("Pylon");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCell(x, y);

  pEntity->features().Int(FeatureNames::ID) = Entity::Pylon;
  pEntity->features().Int(FeatureNames::maxHP) = 100;
  pEntity->features().Int(FeatureNames::HP) = 100;
  pEntity->features().Bool(FeatureNames::generator) = false;
  pEntity->features().Bool(FeatureNames::physic) = true;
}

void Pylon::update() {
  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);

  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->setPosition(pEntity->pos().x, pEntity->pos().y);
}

void Pylon::init() {
  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}