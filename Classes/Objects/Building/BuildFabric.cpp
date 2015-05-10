#include "BuildFabric.h"

#include "MainBase.h"

using namespace Objects::Building;

std::shared_ptr<Build> BuildFabric::create(std::string bId, size_t x, size_t y) {
  if ("MainBase" == bId) {
    return MainBase::create(x, y);
  }
}