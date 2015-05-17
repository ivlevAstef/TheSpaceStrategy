/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_BUILDING_MINERALS_H__
#define _OBJECTS_BUILDING_MINERALS_H__

#include "Build.h"

namespace Objects
{
  namespace Building
  {
    class Minerals: public Build {
    public:
      static std::shared_ptr<Minerals> create(int x, int y);

      Minerals(int x, int y);

      virtual void update() override;

    private:
      void init();

    };
  };
};


#endif // _OBJECTS_BUILDING_MINERALS_H__
