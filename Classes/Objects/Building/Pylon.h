/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_PYLON_H__
#define _OBJECTS_BUILDING_PYLON_H__

#include "Build.h"

namespace Objects
{
  namespace Building
  {
    class Pylon: public Build {
    public:
      static std::shared_ptr<Pylon> create(int x, int y);

      Pylon(int x, int y);

      virtual void update() override;

    private:
      void init();

    };
  };
};


#endif // _OBJECTS_BUILDING_PYLON_H__
