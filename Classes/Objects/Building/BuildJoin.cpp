#include "BuildJoin.h"
#include "Components/View/GameView.h"

using namespace Objects::Building;
using namespace Components::View;

std::shared_ptr<BuildJoin> BuildJoin::create() {
  return std::make_shared<BuildJoin>();
}

BuildJoin::BuildJoin() {
  /*auto view = GameView::create("MainBase");
  addComponent(view);*/
}
