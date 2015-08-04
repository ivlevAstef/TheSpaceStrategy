//
//File: Entity.h
//Description: Class base model type.
//Author: Ivlev Alexander. Stef
//Created: 02/05/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_H__

#include "Common/ModelMath.h"
#include "Common/Features.h"
#include "Common/EntityMutex.h"
#include "Properties/PropertyContainer.h"
#include "Actions/Process.h"
#include <memory>
#include <functional>

namespace Models
{
  class Entity {
  public:
    class Factory;
    friend class Factory;
  public:
    void update();

    void draw(std::function<void(const Entity& entity, double dt)> drawFunc);

    void setPos(Common::EntityPos pos);
    inline void setPos(double x, double y) { setPos({x, y}); }
    inline const Common::EntityPos& pos() const {
      return m_pos;
    }

    inline const Common::EntityPos& lastPos() const {
      return m_lastPos;
    }

    inline const Common::Features& features() { return *m_pFeatures.get(); }

    Properties::PropertyContainer& prop() {
      return m_properties;
    }

    Actions::Process& proc() {
      return m_process;
    }

  protected:
    Entity();
    Entity(const Entity&) = delete;

    Common::EntityPos m_pos;
    Common::EntityPos m_lastPos;

    Common::FeaturesPtr m_pFeatures;

    Common::EntityMutex m_mutex;

    Properties::PropertyContainer m_properties;
    Actions::Process m_process;
  };

  typedef std::shared_ptr<Entity> EntityPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_H__
