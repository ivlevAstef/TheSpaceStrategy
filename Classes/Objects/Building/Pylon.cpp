#include "Pylon.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<Pylon> Pylon::create(size_t x, size_t y) {
  return std::make_shared<Pylon>(x, y);
}

Pylon::Pylon(size_t x, size_t y) {
  auto pView = GameView::create("Pylon");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCellPos(x, y);

  auto pFeatures = getComponent<Features>();
  SIA_ASSERT(pFeatures != nullptr);
  auto features = *pFeatures;

  features[FeatureNames::ID] = Entity::Pylon;
  features[FeatureNames::maxHP] = 100;
  features[FeatureNames::HP] = 100;
  features[FeatureNames::physic] = true;
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