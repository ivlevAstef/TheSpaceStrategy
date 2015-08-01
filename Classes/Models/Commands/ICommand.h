//
//File: ICommand.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 7:34 25/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_I_COMMAND_H__
#define _SIA_THE_SPACE_STRATEGY_I_COMMAND_H__

#include <memory>
#include <functional>
#include "Utils/SIAEvent.h"

#include "../Area.h"

namespace Commands
{
  class CommandController;
  class ICommand {
  private:
    friend class CommandController;

    virtual void perform(Models::AreaPtr pArea) = 0;
  
    typedef SIA::Delegate<bool> DCompleted;///success, failed
    SIA::FriendEvent<ICommand, bool> completed;

  protected:
    void done(bool lSuccess) {
      completed(lSuccess);
    }
  };

  typedef std::shared_ptr<ICommand> CommandPtr;
};

#endif //_SIA_THE_SPACE_STRATEGY_I_COMMAND_H__