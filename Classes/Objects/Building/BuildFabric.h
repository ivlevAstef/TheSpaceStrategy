/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_BUILD_FABRIC_H__
#define _OBJECTS_BUILDING_BUILD_FABRIC_H__

#include "Build.h"

namespace Objects
{
  namespace Building
  {
    class BuildFabric {
    public:
      static std::shared_ptr<Build> create(std::string bId, size_t x, size_t y);
    };
  }
}


#endif // _OBJECTS_BUILDING_BUILD_FABRIC_H__
