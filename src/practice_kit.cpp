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
#include <QDebug>
#include <QThread>
#include <QTreeWidget>

namespace hinan {
PracticeKit::PracticeKit() {
  reader          = new ProgramReader();
  manager         = new PortManager();
  reader_thread_  = new QThread(this);
  manager_thread_ = new QThread(this);
  reader->moveToThread(reader_thread_);
  manager->moveToThread(manager_thread_);
  // When called this->LaunchScript(), call Run() on reader and manager
  connect(this, &PracticeKit::Launch, reader, &ProgramReader::Run);
  connect(this, &PracticeKit::Launch, manager, &PortManager::Run);
  reader_thread_->start();
  manager_thread_->start();
}
PracticeKit::~PracticeKit() {
  reader_thread_->quit();
  reader_thread_->wait();
  manager_thread_->quit();
  manager_thread_->wait();
}

PracticeKit& PracticeKit::Instance() {
  static PracticeKit kit;
  return kit;
}

void PracticeKit::ReloadScript() {
  reader->Terminate();
  reader->Load();
}

void PracticeKit::LaunchScript() { emit Launch(); }
void PracticeKit::TerminateScript() { reader->Terminate(); }

// When script is working, terminate
// When script is not working, launch
void PracticeKit::StartStop() {
  if (reader->IsActive()) {
    TerminateScript();
  } else {
    LaunchScript();
  }
}

int PracticeKit::GetPortStat(QString port) { return manager->Value(port); }
QTreeWidget* PracticeKit::PortStatusWidget() {
  return manager->PortStatusWidget();
}
} // namespace hinan
