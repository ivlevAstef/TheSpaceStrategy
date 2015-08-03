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
#include <thread>
#include <atomic>

namespace Models
{
  class ModelController {
  public:
    typedef Commands::CommandController::Callback CommandCallback;
  
  public:
    ModelController();

    void setArea(AreaPtr pArea);

    void start();

    void pause();
    void resume();

    void stop();

    void addCommand(Commands::CommandPtr command, CommandCallback success, CommandCallback failed);

    void callCommandsCallback();

    inline AreaPtr area() const { return m_pArea; }

    ~ModelController();

  private:
    void update();

    void run();

  private:
    Commands::CommandController m_commandController;

    AreaPtr m_pArea;
    std::thread m_thread;
    std::atomic_bool m_pause;
    std::atomic_bool m_runing;
  };
};

#endif //_SIA_THE_SPACE_STRATEGY_MODEL_CONTROLLER_H__