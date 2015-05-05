/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_MAIN_BASE_H__
#define _OBJECTS_MAIN_BASE_H__

#include "Build.h"

namespace Objects
{
  namespace Building
  {
    class MainBase : public Build {
    public:
      static std::shared_ptr<MainBase> create(int x, int y);

      MainBase(int x, int y);

      virtual void update() override;

    private:
      void init();

    };
  };
};

#endif // _OBJECTS_MAIN_BASE_H__
