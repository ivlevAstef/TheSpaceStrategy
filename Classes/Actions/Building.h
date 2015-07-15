//
//File: Building.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:46 14/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_BUILDING_H__
#define _SIA_THE_SPACE_STRATEGY_BUILDING_H__

#include "Action.h"

namespace Actions
{
  class Building : public Action {
  public:

    static State sComplete;

  public:
    Building(Properties::PropertyContainer& properties, const Common::Features& setting);

    static const char* actionName() { return "building"; }
    static ActionDataPtr createActionData(double buildingTime);

    inline double progress() const { return m_currentTime / m_buildingTime; }

    virtual State update(double dt) override;

  private:
    void begin();
    void end();

  private:
    double m_buildingTime;
    double m_currentTime = 0;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_BUILDING_H__
