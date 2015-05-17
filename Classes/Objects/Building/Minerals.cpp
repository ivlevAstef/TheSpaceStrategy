#include "Minerals.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<Minerals> Minerals::create(int x, int y) {
  return std::make_shared<Minerals>(x, y);
}

Minerals::Minerals(int x, int y) {
  auto pView = GameView::create("Minerals");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCell(x, y);

  pEntity->features().Int(FeatureNames::ID) = Entity::Minerals;
  pEntity->features().Int(FeatureNames::maxHP) = 1000;
  pEntity->features().Int(FeatureNames::HP) = 1000;
  pEntity->features().Bool(FeatureNames::generator) = false;
  pEntity->features().Bool(FeatureNames::physic) = true;
}

void Minerals::update() {
  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);

  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->setPosition(pEntity->pos().x, pEntity->pos().y);
}

void Minerals::init() {
  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}