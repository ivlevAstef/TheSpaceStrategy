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

namespace Models
{
  class ICommand {
  private:

    void execute(double dt);
  };
};

#endif //_SIA_THE_SPACE_STRATEGY_I_COMMAND_H__