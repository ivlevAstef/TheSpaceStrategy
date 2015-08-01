#include "ModelController.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Models);
using namespace Models;

ModelController::ModelController() {
  m_runing = false;
}

void ModelController::setArea(AreaPtr pArea) {
  SIAFatalAssert(pArea);
  m_pArea = pArea;
}

void ModelController::start() {
  SIADebug("Model Controller Start.");
  m_pause = false;
  m_runing = true;
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

void ModelController::stop() {
  SIADebug("Model Controller Stop.");
  m_runing = false;
}

void ModelController::addCommand(Commands::CommandPtr command, CommandCallback success, CommandCallback failed) {
  SIAAssertMsg(m_runing, "You can't add command, if don't run thread (call method start)");

  m_commandController.addCommand(command, success, failed);
}

void ModelController::callCommandsCallback() {
  m_commandController.callCallbacks();
}

IGridDrawPtr ModelController::grid() {
  SIAFatalAssert(m_pArea);
  return m_pArea->grid();
}

ModelController::~ModelController() {
  stop();
}


void ModelController::update() {
  SIAFatalAssert(m_pArea);

  m_commandController.update(m_pArea);
  m_pArea->update();
}

void ModelController::run() {
  while (m_runing) {
    if (!m_pause) {
      update();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}