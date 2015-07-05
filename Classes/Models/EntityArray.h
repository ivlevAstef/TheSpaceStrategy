//
//File: EntityArray.h
//Description: Class for contained entities.
//Author: Ivlev Alexander. Stef
//Created: 05/07/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_ARRAY_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_ARRAY_H__

#include "Entity.h"
#include "Components/IComponent.h"
#include <vector>
#include <functional>

namespace Models
{
  class EntityArray {
  public:
    ///if return true -> continue find, else break.
    typedef std::function<bool(EntityPtr entity)> FindResultCallback;
  public:
    bool add(EntityPtr pEntity);
    bool remove(EntityPtr pEntity);

    void foreachCell(Common::CellPos pos, FindResultCallback callback) const;

    void foreach(FindResultCallback callback) const;

  private:
    std::vector<EntityPtr> m_pEntities;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_ARRAY_H__
