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

#include "State.h"

namespace States
{
  class Building : public State {
  public:
    static std::string Name;

    static StateStatus sComplete;

  public:
    Building(Properties::PropertyContainer& properties, const Common::Features& setting);

    static Common::Features createSetting(double buildingTime);

    inline double progress() const { return m_currentTime / m_buildingTime; }

    virtual StateStatus update(double dt) override;

  private:
    double m_buildingTime;
    double m_currentTime = 0;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_BUILDING_H__
