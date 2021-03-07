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

namespace hinan {
PracticeKit::PracticeKit(QString path) {
  reader_         = new ProgramReader(path);
  manager_        = new PortManager(reader_);
  reader_thread_  = new QThread(this);
  manager_thread_ = new QThread(this);
  reader_->moveToThread(reader_thread_);
  manager_->moveToThread(manager_thread_);
  // When called this->LaunchScript(), call Run() on reader and manager
  connect(this, SIGNAL(Launch()), reader_, SLOT(Run()));
  connect(this, SIGNAL(Launch()), manager_, SLOT(Run()));
  reader_thread_->start();
  manager_thread_->start();
}
PracticeKit::~PracticeKit() {
  reader_thread_->quit();
  reader_thread_->wait();
  manager_thread_->quit();
  manager_thread_->wait();
}

void PracticeKit::ReloadScript() {
  reader_->Terminate();
  reader_->Load();
}

void PracticeKit::LaunchScript() { emit Launch(); }
void PracticeKit::TerminateScript() { reader_->Terminate(); }
int  PracticeKit::GetPortStat(const char* port) {
  return reader_->GetPortStat(port);
}
} // namespace hinan
