// HINAN - simulate H8 microcomputer practice kit
// program-reader_manager.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "program_reader_manager.h"
#include <QDebug>
#include <QThread>

namespace hinan {
ProgramReaderManager::ProgramReaderManager(QString path) {
  reader_thread_ = new QThread(this);
  reader_        = new ProgramReader(path);
  reader_->moveToThread(reader_thread_);
  // When called this->LaunchScript(), call reader_->Run()
  connect(this, SIGNAL(Launch()), reader_, SLOT(Run()));
  connect(this, SIGNAL(Terminate()), reader_, SLOT(Terminate()));
  reader_thread_->start();
}
ProgramReaderManager::~ProgramReaderManager() {
  reader_thread_->quit();
  reader_thread_->wait();
}

void ProgramReaderManager::Reload() {
  reader_->Terminate();
  reader_->Load();
}

void ProgramReaderManager::LaunchScript() { emit Launch(); }
void ProgramReaderManager::TerminateScript() {
  reader_->Terminate();
}
int ProgramReaderManager::GetPortStat(const char* port) {
  return reader_->GetPortStat(port);
}
} // namespace hinan
