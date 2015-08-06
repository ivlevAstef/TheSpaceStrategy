//
//File: Action.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:47 14/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ACTION_H__
#define _SIA_THE_SPACE_STRATEGY_ACTION_H__

#include "Properties/PropertyContainer.h"
#include "Common/Features.h"
#include <string>
#include <memory>

namespace Actions
{
  class Action;
  typedef std::shared_ptr<Action> ActionPtr;

  class Action {
  public:
    class Factory;
    friend class Factory;

    typedef std::string State;//e.g. "Executing", "Death"

    static State sExecuting;
    static State sDeath;

  public:

    Action(Properties::PropertyContainer& properties);
    Action(const Action&) = delete;
    Action& operator=(const Action&) = delete;
    
    virtual State update(double dt) = 0;

  protected:

    inline Properties::PropertyContainer& properties() {
      return m_properties;
    }

    bool checkDeath();

  private:

    Properties::PropertyContainer& m_properties;
  };

  class ActionData {
  public:
    ActionData(std::string name, const Common::Features setting) : m_name(name), m_setting(setting) {
    }
    ActionData(const ActionData&) = delete;
    ActionData& operator=(const ActionData&) = delete;

    inline std::string name() const { return m_name; }
    inline const Common::Features& setting() const { return m_setting; }

  private:
    std::string m_name;
    const Common::Features m_setting;
  };

  typedef std::shared_ptr<ActionData> ActionDataPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_ACTION_H__
