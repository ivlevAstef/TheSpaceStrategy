//
//File: CommandController.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 7:35 25/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_COMMAND_CONTROLLER_H__
#define _SIA_THE_SPACE_STRATEGY_COMMAND_CONTROLLER_H__

#include "ICommand.h"
#include <stack>
#include <mutex>

namespace Commands
{
  class CommandController {
  public:
    typedef std::function<void()> Callback;

  public:
    void addCommand(CommandPtr command, Callback success, Callback failed);

    void update(Models::AreaPtr pArea);

    void callCallbacks();

  private:
    std::stack<CommandPtr> m_commands;
    std::list<Callback> m_callbacks;

    std::mutex m_mutex;
  };
};

#endif //_SIA_THE_SPACE_STRATEGY_COMMAND_CONTROLLER_H__