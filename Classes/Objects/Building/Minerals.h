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
      static std::shared_ptr<Minerals> create(size_t x, size_t y);

      Minerals(size_t x, size_t y);

      virtual void update() override;

    private:
      void init();

    };
  };
};


#endif // _OBJECTS_BUILDING_MINERALS_H__
