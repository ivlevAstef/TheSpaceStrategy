//
//File: Area.h
//Description: Class with Area data (Store entities and size) 
//Author: Ivlev Alexander. Stef
//Created: 02/05/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_AREA_H__
#define _SIA_THE_SPACE_STRATEGY_AREA_H__

#include "Entities.h"
#include "Entities_Array.h"
#include "Entities_Grid.h"
#include "Entities_Graph.h"

namespace Models
{
  class Area: SIA::NonCopyable {
  private:
    static const size_t MaxEntitiesCount = 2048;
  public:
    Area(size_t width, size_t height);

    bool addEntity(EntityPtr pEntity);
    bool eraseEntity(EntityPtr pEntity);

    void update();

    size_t width() const;
    size_t height() const;

  private:
    bool setupEntity(EntityPtr pEntity);

  private:
    Entities m_entities;
  };

  typedef std::shared_ptr<Area> AreaPtr;
  typedef std::shared_ptr<const Area> ConstAreaPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_AREA_H__
