//
//File: EntitiesArray.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 20:41 30/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITIES_ARRAY_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITIES_ARRAY_H__

#include "Entities.h"
#include <vector>
#include <functional>

namespace Models
{
  class Entities::Array : SIA::NonCopyable {
  public:
    ///if return true -> continue find, else break.
    typedef std::function<bool(EntityPtr entity)> FindResultCallback;
  public:
    Array(const Entities&, size_t maxCount);

    bool add(EntityPtr pEntity);
    void update(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);

    void update();

    void foreachCell(Common::CellPos pos, FindResultCallback callback) const;

    void foreach(FindResultCallback callback) const;    

  private:
    const Entities& m_parent;

    size_t m_maxCount;
    std::vector<EntityPtr> m_pEntities;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITIES_ARRAY_H__
