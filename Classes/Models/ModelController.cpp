#include "ModelController.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Models);
using namespace Models;

void ModelController::setArea(AreaPtr pArea) {
  SIAFatalAssert(pArea);
  m_pArea = pArea;
}

void ModelController::pause() {
  SIADebug("Model Controller Pause.");
}

void ModelController::resume() {
  SIADebug("Model Controller Resume.");
}

void ModelController::addCommand(Commands::CommandPtr command, CommandCallback success, CommandCallback failed) {
  m_commandController.addCommand(command, success, failed);
}

void ModelController::callCommandsCallback() {
  m_commandController.callCallbacks();
}

IGridDrawPtr ModelController::grid() {
  SIAFatalAssert(m_pArea);
  return m_pArea->grid();
}


void ModelController::update() {
  SIAFatalAssert(m_pArea);

  m_commandController.update(m_pArea);
  m_pArea->update();
}