// HINAN - simulate H8 microcomputer practice kit
// toggle_switches.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/toggle_switches.h"
#include "port/port.h"
#include "port_manager.h"
#include "practice_kit.h"
#include <QApplication>
#include <QIcon>
#include <QLayout>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
ToggleSwitches::ToggleSwitches(QWidget* parent)
    : ComponentInterface(parent, 345, 230, 120, 50) {
  // Load pictures
  icon_[0] = QIcon(
      QPixmap(QApplication::applicationDirPath() + "/assets/toggle-low.png"));
  icon_[1] = QIcon(
      QPixmap(QApplication::applicationDirPath() + "/assets/toggle-high.png"));

  setStyleSheet("QPushButton:checked{ background-color: rgba(0,0,0,100%) }");
  QHBoxLayout* layout = new QHBoxLayout();
  switches_.resize(5);
  for (int i = 0; i < switches_.size(); i++) {
    switches_[i] = new QPushButton(this);
    switches_[i]->setCheckable(true);
    switches_[i]->setFlat(true);
    switches_[i]->setAutoFillBackground(false);
    switches_[i]->setSizePolicy(
        QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    switches_[i]->setIcon(icon_[0]);
    switches_[i]->setIconSize(switches_[i]->size());
    layout->addWidget(switches_[i]);
    connect(switches_[i], &QPushButton::toggled, this,
            &ToggleSwitches::ChangeIcon);
  }
  setLayout(layout);
}

void ToggleSwitches::Update() {
  const int P2DDR =
      PracticeKit::Instance().port_manager->GetPortValue(port::P2DDR);
  int result = 0;
  for (int i = switches_.size() - 1; i >= 0; i--) {
    result  = result << 1;
    int pos = 1 << i;
    if (!switches_[i]->isChecked() && !(P2DDR & pos)) {
      ++result;
    }
  }
  // Lower 3 bit of P2DR is fixed 1 (reserve)
  result = (result << 3) + 0b111;
  PracticeKit::Instance().port_manager->SetPortValue(port::P2DR, result);
  QApplication::processEvents();
}

void ToggleSwitches::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  for (auto obj : switches_) {
    obj->setIconSize(obj->size());
  }
}

void ToggleSwitches::ChangeIcon() {
  for (auto obj : switches_) {
    obj->setIcon(icon_[obj->isChecked()]);
    QApplication::processEvents();
  }
}
} // namespace components
} // namespace hinan