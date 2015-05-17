#include "BuildFabric.h"

#include "MainBase.h"
#include "Pylon.h"
#include "GetterMineral.h"
#include "Minerals.h"

using namespace Objects::Building;

std::shared_ptr<Build> BuildFabric::create(std::string bId, size_t x, size_t y) {
  if ("MainBase" == bId) {
    return MainBase::create(x, y);
  }
  if ("Pylon" == bId) {
    return Pylon::create(x, y);
  }
  if ("GetterMineral" == bId) {
    return GetterMineral::create(x, y);
  }

  if ("Minerals" == bId) {
    return Minerals::create(x, y);
  }
}