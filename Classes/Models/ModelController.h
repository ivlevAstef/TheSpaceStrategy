//
//File: ModelController.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 22:24 26/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_MODEL_CONTROLLER_H__
#define _SIA_THE_SPACE_STRATEGY_MODEL_CONTROLLER_H__

#include "Commands/CommandController.h"
#include "Area.h"

namespace Models
{
  class ModelController {
  public:
    typedef Commands::CommandController::Callback CommandCallback;
  
  public:
    void setArea(AreaPtr pArea);

    void pause();
    void resume();

    void addCommand(Commands::CommandPtr command, CommandCallback success, CommandCallback failed);

    void callCommandsCallback();

    IGridDrawPtr grid();

  public:///private
    void update();

  private:
    Commands::CommandController m_commandController;

    AreaPtr m_pArea;
  };
};

#endif //_SIA_THE_SPACE_STRATEGY_MODEL_CONTROLLER_H__