//
//File: Action.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 10:16 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#include "Action.h"

using namespace Actions;

Action::State Action::sExecuting = "executing";
Action::State Action::sDeath = "death";

Action::Action(Properties::PropertyContainer& properties) : m_properties(properties) {

}

bool Action::checkDeath() {
  return false;
}