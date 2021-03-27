// HINAN - simulate H8 microcomputer practice kit
// components_manager.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components_manager.h"
#include "components/component_interface.h"
#include "components/led.h"
#include "components/segment.h"
#include "components/tact_switches.h"
#include "components/toggle_switches.h"
#include "port/port.h"
#include "practice_kit.h"
#include <QApplication>
#include <QRect>
#include <QThread>
#include <QTreeWidget>
#include <QVector>
#include <QWidget>

QRect Expantion(QRect base, double rate) {
  base.setRect(base.x() * rate, base.y() * rate, base.width() * rate,
               base.height() * rate);
  return base;
}

namespace hinan {
ComponentsManager::ComponentsManager()
    : widget_(new QWidget), isTerminated_(false) {
  components_.append(new components::LED(widget_));
  components_.append(new components::Segment(widget_));
  components_.append(new components::TactSwitches(widget_));
  components_.append(new components::ToggleSwitches(widget_));
  for (auto obj : components_) {
    obj->setGeometry(obj->OriginalSize());
  }
  InitPortStatus();
}
ComponentsManager::~ComponentsManager() { qDebug("Deleted ComponentsManager"); }

void ComponentsManager::SetWidgetsParent(QWidget* parent) {
  widget_->setParent(parent);
}

void ComponentsManager::Update() {
  for (auto obj : components_) {
    if (!PracticeKit::Instance().reader->IsActive()) {
      qDebug("[ComponentMgr] Failed: Reader is not active");
      return;
    }
    obj->Update();
    QApplication::processEvents();
  }
  UpdatePortStatus();
}

QTreeWidget* ComponentsManager::PortStatusWidget() {
  return port_status_widget_;
}
void ComponentsManager::InitPortStatus() {
  qDebug("init");
  port_status_widget_ = new QTreeWidget;
  port_status_widget_->setColumnCount(4);
  port_status_widget_->setColumnWidth(0, 100);
  port_status_widget_->setColumnWidth(1, 50);
  port_status_widget_->setColumnWidth(2, 80);
  port_status_widget_->setColumnWidth(3, 45);
  port_status_widget_->setHeaderLabels(
      {tr("Value"), tr("HEX"), tr("BIN"), tr("DEC")});
  QTreeWidgetItem* direction = new QTreeWidgetItem(port_status_widget_);
  QTreeWidgetItem* data      = new QTreeWidgetItem(port_status_widget_);
  direction->setText(0, tr("Direction"));
  data->setText(0, tr("Data"));
  direction->setExpanded(true);
  data->setExpanded(true);
  port_status_widget_->addTopLevelItem(direction);
  port_status_widget_->addTopLevelItem(data);

  // Initialize data direction register
  int              i = 0;
  QTreeWidgetItem* item;
  for (auto str : port::port_ddr) {
    item = new QTreeWidgetItem(direction);
    direction->addChild(item);
    port_status_.insert(str, direction->child(i));
    ++i;
  }
  i = 0;
  // Initialize data register
  for (auto str : port::port_dr) {
    item = new QTreeWidgetItem(data);
    data->addChild(item);
    port_status_.insert(str, data->child(i));
    ++i;
  }
  for (auto str : port::port_list) {
    port_status_[str]->setText(0, str);
    port_status_[str]->setText(1, "0x00");
    port_status_[str]->setText(2, "00000000");
    port_status_[str]->setText(3, "0");
  }
}

void ComponentsManager::UpdatePortStatus() {
  for (auto str : port::port_list) {
    int     value = PracticeKit::Instance().reader->GetPortValue(str);
    QString hex   = QString::asprintf("0x%02x", value);
    // convert DEC->BIN (Ex. 13->1101)
    QString bin = "";
    for (int i = 0; i < 8; i++) {
      bin += QString::number((value >> i) & 1);
    }
    std::reverse(bin.begin(), bin.end());
    port_status_[str]->setText(1, hex);
    port_status_[str]->setText(2, bin);
    port_status_[str]->setText(3, QString::number(value));
    QApplication::processEvents();
  }
}

void ComponentsManager::Run() {
  isTerminated_ = false;
  qDebug("[ComponentMgr] Start run");
  while (PracticeKit::Instance().reader->IsActive() && !isTerminated_) {
    Update();
    QThread::msleep(10);
  }
  isTerminated_ = false;
  qDebug("[ComponentMgr] Finish run");
}

void ComponentsManager::Terminate() {
  qDebug("[ComponentsMgr] Terminated");
  isTerminated_ = true;
}

void ComponentsManager::Resize(QSize parent_size, double expantion_rate) {
  widget_->resize(parent_size);
  for (auto obj : components_) {
    obj->setGeometry(Expantion(obj->OriginalSize(), expantion_rate));
  }
}
} // namespace hinan
