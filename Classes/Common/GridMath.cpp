#include "GridMath.h"
#include "SIALogger.h"
#include <cmath>

using namespace Common;
USING_NS_CC;

const double GridMath::GridCellSize = 100;

cocos2d::Vec2 GridMath::convert(double u, double v) {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  return Vec2(x * GridCellSize + GridCellSize*0.5,
              y * GridCellSize + GridCellSize*0.5);
#elif defined(USE_6_MODEL)
  return Vec2(GridCellSize*SQRT3*0.5 * (u - v),
    GridCellSize*0.5 * (u + v));
#else
#error Defined Model Type
#endif
}

SIAUtils::Point2D<double> GridMath::convert(cocos2d::Vec2 pos) {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  double u = pos.x / GridCellSize;
  double v = pos.y / GridCellSize;
#elif defined(USE_6_MODEL)
  double u = (pos.x + pos.y*SQRT3) / (SQRT3 * GridCellSize);
  double v = (pos.y*SQRT3 - pos.x) / (SQRT3 * GridCellSize);
#else
#error Defined Model Type
#endif
  return {u, v};
}

static void normalize(int& value, size_t size) {
  value += size * (value < 0 ? (1 + (size_t)(-value / size)) : -(size_t)(value / size));
}

static SIAUtils::Point2D<size_t> normalize(int x, int y, size_t width, size_t height) {
  normalize(x, width);
  normalize(y, height);
  return SIAUtils::Point2D<size_t>(x, y);
}

SIAUtils::Point2D<size_t> GridMath::cell(double u, double v, size_t width, size_t height) {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  return normalize(u, v, width, height);
#elif defined(USE_6_MODEL)
  int uZero = u;///floor
  int vZero = v;///floor

  double uN = u - (double)uZero;
  double vN = v - (double)vZero;

  bool uSmall = uN < 0.5;
  bool vSmall = vN < 0.5;

  if (!(uSmall ^ vSmall)) {///(x > 0.5 y > 0.5) or ( x < 0.5 y < 0.5)
    return normalize(uZero + !uSmall, vZero + !vSmall, width, height);
  }

  ///x > 0.5 y < 0.5
  if (!uSmall && vSmall) {
    size_t uT = (1 + vN < 2.0 * uN) ? 1 : 0;
    size_t vT = (uN < 2.0 * vN) ? 1 : 0;
    if (0 == uT && 1 == vT) {
      uT = vT = (uN < 1.0 - vN) ? 0 : 1;
    }

    return normalize(uZero + uT, vZero + vT, width, height);
  } else { ///y > 0.5 x < 0.5
    size_t uT = (vN < 2.0 * uN) ? 1 : 0;
    size_t vT = (1 + uN < 2.0 * vN) ? 1 : 0;
    if (0 == vT && 1 == uT) {
      uT = vT = (vN < 1.0 - uN) ? 0 : 1;
    }

    return normalize(uZero + uT, vZero + vT, width, height);
  }
#else
#error Defined Model Type
#endif
}


cocos2d::Vec2 GridMath::center(size_t x, size_t y) {
  return convert(x, y);
}

cocos2d::Vec2 GridMath::build(size_t x, size_t y, size_t index) {
  SIAAssert(index < MaxCellBuilds);
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  static const Vec2 translated[MaxCellBuilds] = {
    Vec2(0, GridCellSize*0.3f),
    Vec2(GridCellSize*0.3f, 0),
    Vec2(0, GridCellSize*-0.3f),
    Vec2(GridCellSize*-0.3f, 0)
  };

  return center(x, y) + translated[index];
#elif defined(USE_6_MODEL)
#define SQRT5 2.23606797749979
  static const Vec2 translated[MaxCellBuilds] = {
    Vec2(0, GridCellSize / 4.0),
    Vec2(GridCellSize*SQRT5 / 8.0, -GridCellSize / 8.0),
    Vec2(-GridCellSize*SQRT5 / 8.0, -GridCellSize / 8.0),
    
  };

  return center(x, y) + translated[index];
#else
#error Defined Model Type
#endif
}


const std::vector<cocos2d::Vec2>& GridMath::cellView() {
  static double cellHalfSize = GridCellSize * 0.5;
#ifdef USE_4_MODEL
  static const std::vector<cocos2d::Vec2> cellPos = {
    Vec2(-cellHalfSize,-cellHalfSize),
    Vec2( cellHalfSize,-cellHalfSize),
    Vec2( cellHalfSize, cellHalfSize),
    Vec2(-cellHalfSize, cellHalfSize)
  };
#elif defined(USE_8_MODEL)
#define SQRT2 1.414213562373095
  static const size_t viewCount = 8;
  static double octaEdge = GridCellSize / (SQRT2 + 1.0);
  static double octaB = GridCellSize / (SQRT2 + 2.0);

  static const std::vector<cocos2d::Vec2> cellPos = {
    Vec2(-cellHalfSize, octaB - cellHalfSize),
    Vec2(-cellHalfSize, octaB + octaEdge - cellHalfSize),
    Vec2(octaB - cellHalfSize, cellHalfSize),
    Vec2(octaB + octaEdge - cellHalfSize, cellHalfSize),
    Vec2(cellHalfSize, octaB + octaEdge - cellHalfSize),
    Vec2(cellHalfSize, octaB - cellHalfSize),
    Vec2(octaB + octaEdge - cellHalfSize, -cellHalfSize),
    Vec2(octaB - cellHalfSize, -cellHalfSize)
  };

#elif defined(USE_6_MODEL)
  static const std::vector<cocos2d::Vec2> cellPos = {
    Vec2(-cellHalfSize / SQRT3, -cellHalfSize),
    Vec2(-GridCellSize / SQRT3, 0),
    Vec2(-cellHalfSize / SQRT3, cellHalfSize),
    Vec2(cellHalfSize / SQRT3, cellHalfSize),
    Vec2(GridCellSize / SQRT3, 0),
    Vec2(cellHalfSize / SQRT3, -cellHalfSize),
    
  };
#else
#error Defined Model Type
#endif
  return cellPos;
}

const std::vector<SIAUtils::Position>& GridMath::neighborhood() {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  static const std::vector<SIAUtils::Position> res = {
    SIAUtils::Position(-1, 0),
    SIAUtils::Position(1 , 0),
    SIAUtils::Position(0 , 1),
    SIAUtils::Position(0 ,-1)
  };
  return res;
#elif defined(USE_6_MODEL)
  static const std::vector<SIAUtils::Position> res = {
    SIAUtils::Position(-1, 0),
    SIAUtils::Position(1 , 0),
    SIAUtils::Position(0 , 1),
    SIAUtils::Position(0 ,-1),
    SIAUtils::Position(-1,-1),
    SIAUtils::Position(1 , 1)
  };
  return res;
#else
#error Defined Model Type
#endif
}
std::vector<SIAUtils::Position> GridMath::neighborhood(size_t x, size_t y) {
  const std::vector<SIAUtils::Position>& neighborhood = GridMath::neighborhood();
  std::vector<SIAUtils::Position> res;
  res.resize(neighborhood.size());
  for (size_t i = 0; i < neighborhood.size(); i++) {
    res[i].x = x + neighborhood[i].x;
    res[i].y = y + neighborhood[i].y;
  }
  return res;
}