#include "MainBase.h"
#include "Components/View/GameView.h"

using namespace Objects;
using namespace Components::View;

std::shared_ptr<MainBase> MainBase::create() {
  return std::make_shared<MainBase>();
}

MainBase::MainBase() {
  auto view = GameView::create("MainBase");
  view->setCell(4, 4);
  addComponent(view);
}