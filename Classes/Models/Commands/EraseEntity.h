//
//File: EraseEntity.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 22:34 26/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_COMMAND_ERASE_ENTITY_H__
#define _SIA_THE_SPACE_STRATEGY_COMMAND_ERASE_ENTITY_H__

#include "ICommand.h"
#include "../Entity.h"

namespace Commands
{
  class EraseEntity: public ICommand {
  public:
    EraseEntity(Models::EntityPtr pEntity);

    virtual void perform(Models::AreaPtr pArea) override;

  private:
    Models::EntityPtr m_pEntity;
  };

  typedef std::shared_ptr<ICommand> CommandPtr;
};

#endif //_SIA_THE_SPACE_STRATEGY_COMMAND_ERASE_ENTITY_H__