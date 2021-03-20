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
#include "practice_kit.h"
#include <QRect>
#include <QVector>
#include <QWidget>
#include <QApplication>

QRect Expantion(QRect base, double rate) {
  auto o = base;
  base.moveTo(base.x() * rate, base.y() * rate);
  base.setWidth(base.width() * rate);
  base.setHeight(base.height() * rate);
  return base;
}

namespace hinan {
ComponentsManager::ComponentsManager()
    : widget_(new QWidget), isTerminated_(false) {
  components_.append(new components::LED(widget_));
  for (auto obj : components_) {
    obj->setGeometry(obj->OriginalSize());
  }
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
  }
}

void ComponentsManager::Run() {
  isTerminated_ = false;
  qDebug("[ComponentMgr] Start run");
  while (PracticeKit::Instance().reader->IsActive() && !isTerminated_) {
    Update();
    QApplication::processEvents();
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
