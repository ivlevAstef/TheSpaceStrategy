/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_BUILD_H__
#define _OBJECTS_BUILDING_BUILD_H__

#include "../Object.h"

namespace Objects
{
  namespace Building
  {
    class Build : public Object {
    public:
      Build();
      virtual ~Build();
    };
  };
};


#endif // _OBJECTS_BUILDING_BUILD_H__
