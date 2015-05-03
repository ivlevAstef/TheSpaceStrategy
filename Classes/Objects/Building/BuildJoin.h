/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_BUILD_JOIN_H__
#define _OBJECTS_BUILDING_BUILD_JOIN_H__

#include "../Object.h"

namespace Objects
{
  namespace Building
  {
    class BuildJoin : public Object {
    public:
      static std::shared_ptr<BuildJoin> create();

      BuildJoin();

      virtual void update() override { }
    };
  };
};

#endif // _OBJECTS_BUILDING_BUILD_JOIN_H__
