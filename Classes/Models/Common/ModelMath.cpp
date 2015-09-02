#include "ModelMath.h"
#include "SIALogger.h"
#include <cmath>

SIASetModuleName(Model);

using namespace Common;

CellPos ModelMath::cell(EntityPos pos) {
  return CellPos((int)pos.x, (int)pos.y);
}

EntityPos ModelMath::center(CellPos pos) {
  return EntityPos((double)pos.x + 0.5, (double)pos.y + 0.5);
}

double ModelMath::distance(EntityPos p1, EntityPos p2) {
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  return sqrt(dx*dx + dy*dy);
}