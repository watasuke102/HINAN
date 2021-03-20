// HINAN - simulate H8 microcomputer practice kit
// practice_kit.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "practice_kit.h"
#include "port_manager.h"
#include "program_reader.h"
#include <QThread>
#include <QTreeWidget>

namespace hinan {
PracticeKit::PracticeKit() {
  reader                     = new ProgramReader;
  port_manager               = new PortManager;
  components_manager         = new ComponentsManager;
  reader_thread_             = new QThread(this);
  port_manager_thread_       = new QThread(this);
  components_manager_thread_ = new QThread(this);
  reader->moveToThread(reader_thread_);
  port_manager->moveToThread(port_manager_thread_);
  components_manager->moveToThread(components_manager_thread_);

  // connect
  connect(this, &PracticeKit::StartStopSignal, this,
          &PracticeKit::StartStopScript);
  connect(this, &PracticeKit::LaunchSignal, reader, &ProgramReader::Run);
  // Port manager
  connect(reader, &ProgramReader::ActivatedSignal, port_manager,
          &PortManager::Run);
  connect(reader, &ProgramReader::DeactivatedSignal, port_manager,
          &PortManager::Terminate);
  // Components manager
  connect(reader, &ProgramReader::ActivatedSignal, components_manager,
          &ComponentsManager::Run);
  connect(reader, &ProgramReader::DeactivatedSignal, components_manager,
          &ComponentsManager::Terminate);

  // Start the threads
  reader_thread_->start();
  port_manager_thread_->start();
  components_manager_thread_->start();
}
PracticeKit::~PracticeKit() {
  reader_thread_->quit();
  reader_thread_->wait();
  port_manager_thread_->quit();
  port_manager_thread_->wait();
  components_manager_thread_->quit();
  components_manager_thread_->wait();
  delete reader;
  delete port_manager;
  delete components_manager;
  qDebug("Deleted PracticeKit");
}

PracticeKit& PracticeKit::Instance() {
  static PracticeKit kit;
  return kit;
}

void PracticeKit::TerminateScript() { reader->Terminate(); }
// When script is working, terminate
// When script is not working, launch
void PracticeKit::StartStopScript() {
  if (reader->IsActive()) {
    reader->Terminate();
  } else {
    emit LaunchSignal();
  }
}
} // namespace hinan
