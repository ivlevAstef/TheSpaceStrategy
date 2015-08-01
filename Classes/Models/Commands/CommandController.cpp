#include "CommandController.h"
#include "../Area.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Commands);
using namespace Commands;

void CommandController::addCommand(CommandPtr command, Callback success, Callback failed) {
  SIAAssert(command);

  std::unique_lock<std::mutex> lk(m_mutex);

  command->completed += ICommand::DCompleted(this, [success, failed, this] (bool successRes) {
    if (successRes && (bool)success) {
      m_callbacks.push_back(success);
      SIAInfo("Add success callback.");
    } else if ((bool)failed) {
      m_callbacks.push_back(failed);
      SIAInfo("Add failed callback.");
    }
  });

  m_commands.push(command);
  SIAInfo("Add command success.");
}

void CommandController::update(Models::AreaPtr pArea) {
  SIAAssert(pArea);
  std::unique_lock<std::mutex> lk(m_mutex);
  SIATrace("Call commands update.");

  while (!m_commands.empty()) {
    CommandPtr command = m_commands.top();
    m_commands.pop();

    if ((bool)command) {
      command->perform(pArea);
    }
  }
}

void CommandController::callCallbacks() {
  std::unique_lock<std::mutex> lk(m_mutex);
  SIATrace("Call commands callbacks.");

  for(auto callback : m_callbacks) {
    SIAAssert(callback);
    callback();
  }

  m_callbacks.clear();
}
