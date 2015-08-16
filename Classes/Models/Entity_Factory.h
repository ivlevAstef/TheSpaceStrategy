//
//File: Entity_Factory.h
//Description: Static class for create Entity.
//Author: Ivlev Alexander. Stef
//Created: 27/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_FACTORY_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_FACTORY_H__

#include "Entity.h"
#include <memory>

namespace Models {
  class Entity::Factory {
  public:
    static EntityPtr createBuildByName(std::string name);

    static Common::EntitySize maxEntitySize();

  private:

    static bool initMainBase(Entity& entity);
    static bool initPylon(Entity& entity);
    static bool initMinerMinerals(Entity& entity);
    static bool initMinerals(Entity& entity);
  };
}

#endif //_SIA_THE_SPACE_STRATEGY_ENTITY_FACTORY_H__