#include "Build.h"
#include "Components/Data/Entity.h"

using namespace Objects::Building;

Build::Build() {
  addComponent(Components::Data::Entity::create());
}