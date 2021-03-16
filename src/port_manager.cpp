// HINAN - simulate H8 microcomputer practice kit
// port_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "port_manager.h"
#include "port/port.h"
#include "practice_kit.h"
#include "program_reader.h"
#include <QDebug>
#include <QLayout>
#include <QTreeWidget>

namespace hinan {
PortManager::PortManager() {
  widget_ = new QTreeWidget;
  widget_->setColumnCount(4);
  widget_->setColumnWidth(0, 100);
  widget_->setColumnWidth(1, 50);
  widget_->setColumnWidth(2, 80);
  widget_->setHeaderLabels({tr("Value"), tr("HEX"), tr("BIN"), tr("DEC")});
  QTreeWidgetItem* direction = new QTreeWidgetItem(widget_);
  QTreeWidgetItem* data      = new QTreeWidgetItem(widget_);
  direction->setText(0, tr("Direction"));
  data->setText(0, tr("Data"));
  direction->setExpanded(true);
  data->setExpanded(true);
  widget_->addTopLevelItem(direction);
  widget_->addTopLevelItem(data);

  // Initialize direction data register
  int              i = 0;
  QTreeWidgetItem* item;
  for (auto str : port::port_ddr) {
    item = new QTreeWidgetItem(direction);
    direction->addChild(item);
    map_.insert(str, new PortStatusItem(0x00, str, direction->child(i)));
    ++i;
  }
  i = 0;
  // Initialize data register
  for (auto str : port::port_dr) {
    item = new QTreeWidgetItem(data);
    data->addChild(item);
    map_.insert(str, new PortStatusItem(0x00, str, data->child(i)));
    ++i;
  }
}

QTreeWidget* PortManager::PortStatusWidget() { return widget_; }

void PortManager::Update() {
  for (auto str : port::port_list) {
    if (!PracticeKit::Instance().reader->IsActive())
      return;
    int stat = PracticeKit::Instance().reader->GetPortStat(str.toUtf8().data());
    if (stat != -1)
      map_[str]->SetValue(stat);
  }
}

void PortManager::Run() {
  while (!PracticeKit::Instance().reader->IsActive())
    ;
  qDebug("[Portmgr] Start run");
  while (PracticeKit::Instance().reader->IsActive())
    Update();
  qDebug("[Portmgr] Finish run");
}

int PortManager::Value(QString port) {
  for (auto str : hinan::port::port_list) {
    if (port == str)
      return map_[port]->Value();
  }
  return -1;
}
} // namespace hinan
