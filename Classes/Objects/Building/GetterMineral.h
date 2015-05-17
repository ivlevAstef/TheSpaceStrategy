/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_GETTER_MINERAL_H__
#define _OBJECTS_BUILDING_GETTER_MINERAL_H__

#include "Build.h"

namespace Objects
{
  namespace Building
  {
    class GetterMineral: public Build {
    public:
      static std::shared_ptr<GetterMineral> create(int x, int y);

      GetterMineral(int x, int y);

      virtual void update() override;

    private:
      void init();

    };
  };
};

#endif // _OBJECTS_BUILDING_GETTER_MINERAL_H__
