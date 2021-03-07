// HINAN - simulate H8 microcomputer practice kit
// port_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "port_manager.h"
#include "port.h"
#include "program_reader.h"
#include <QDebug>

namespace hinan {
PortManager::PortManager(ProgramReader* reader) : reader_(reader) {
  for (auto str : port::port_list)
    map_.insert(str, 0x00);
}

void PortManager::Update() {
  for (auto str : port::port_list) {
    if(!reader_->IsActive())
      return;
    int stat = reader_->GetPortStat(str.toUtf8().data());
    if (stat != -1)
      map_[str] = stat;
  }
}

void PortManager::Run() {
  while (!reader_->IsActive())
    ;
  qDebug("[Portmgr] Start run");
  while (reader_->IsActive())
    Update();
  qDebug("[Portmgr] Finish run");
}

int PortManager::Value(QString port) {
  for (auto str : hinan::port::port_list) {
    if (port == str)
      return map_[port];
  }
  return -1;
}
} // namespace hinan