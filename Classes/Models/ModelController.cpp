#include "ModelController.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Models);
using namespace Models;

ModelController::ModelController() {
}

void ModelController::setArea(AreaPtr pArea) {
  SIAFatalAssert(pArea);
  m_pArea = pArea;
}

void ModelController::start() {
  SIADebug("Model Controller Start.");
  m_pause = false;
  m_thread = std::thread(&ModelController::run, this);
  m_thread.detach();
}

void ModelController::pause() {
  SIADebug("Model Controller Pause.");
  m_pause = true;
}

void ModelController::resume() {
  SIADebug("Model Controller Resume.");
  m_pause = false;
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

void ModelController::run() {
  while (true) {
    if (!m_pause) {
      update();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}