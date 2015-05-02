/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_MAIN_BASE_H__
#define _OBJECTS_MAIN_BASE_H__

#include "Object.h"

namespace Objects
{
  class MainBase: public Object {
  public:
  public:
    static std::shared_ptr<MainBase> create();

    MainBase();
  };
};

#endif // _OBJECTS_MAIN_BASE_H__
