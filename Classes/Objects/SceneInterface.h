/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_SCENE_INTERFACE_H__
#define _SIA_THE_SPACE_STRATEGY_SCENE_INTERFACE_H__

#include "Views/Common/ViewMath.h"
#include <memory>

namespace Objects
{
  class SceneInterface {
  public:
    virtual const Common::ViewMath& viewMath() const = 0;
  };

  typedef std::shared_ptr<SceneInterface> SceneInterfacePtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_SCENE_INTERFACE_H__
