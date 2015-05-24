#include "GetterMineral.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<GetterMineral> GetterMineral::create(size_t x, size_t y) {
  return std::make_shared<GetterMineral>(x, y);
}

GetterMineral::GetterMineral(size_t x, size_t y) {
  auto pView = GameView::create("GetterMineral");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCellPos(x, y);

  auto pFeatures = getComponent<Features>();
  SIA_ASSERT(pFeatures != nullptr);
  auto features = *pFeatures;

  features[FeatureNames::ID] = Entity::GetterMineral;
  features[FeatureNames::maxHP] = 50;
  features[FeatureNames::HP] = 50;
  features[FeatureNames::physic] = true;
}

void GetterMineral::update() {
  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);

  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->setPosition(pEntity->pos().x, pEntity->pos().y);
}

void GetterMineral::init() {
  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}