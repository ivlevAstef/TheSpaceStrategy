//
//File: EntityMutex.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 8:00 25/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_MUTEX_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_MUTEX_H__

namespace Common
{
  class EntityMutex {
  public:
    void BeginDraw();
    void EndDraw();

    void BeginUpdate();
    void EndUpdate();

    double deltaTime() const;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_MUTEX_H__
