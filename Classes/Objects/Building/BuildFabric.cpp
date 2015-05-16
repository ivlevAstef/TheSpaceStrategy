#include "BuildFabric.h"

#include "MainBase.h"
#include "Pylon.h"

using namespace Objects::Building;

std::shared_ptr<Build> BuildFabric::create(std::string bId, size_t x, size_t y) {
  if ("MainBase" == bId) {
    return MainBase::create(x, y);
  }
  if ("Pylon" == bId) {
    return Pylon::create(x, y);
  }
}