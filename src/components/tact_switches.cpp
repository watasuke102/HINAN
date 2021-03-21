// HINAN - simulate H8 microcomputer practice kit
// tact_switches.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/tact_switches.h"
#include "port/port.h"
#include "port_manager.h"
#include "practice_kit.h"
#include <QLayout>
#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
TactSwitches::TactSwitches(QWidget* parent)
    : ComponentInterface(parent, 350, 250, 90, 35) {
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setSpacing(3);
  switches_.resize(4);
  for (int i = 0; i < switches_.size(); i++) {
    switches_[i] = new QPushButton(this);
    switches_[i]->setCheckable(true);
    layout->addWidget(switches_[i]);
  }
  setLayout(layout);
}

void TactSwitches::Update() {
  const int P5DDR =
      PracticeKit::Instance().port_manager->GetPortValue(port::P5DDR);
  int result = 0;
  for (int i = switches_.size() - 1; i >= 0; i--) {
    result  = result << 1;
    int pos = 1 << i;
    if (!switches_[i]->isDown() && !(P5DDR & pos)) {
      ++result;
    }
  }
  PracticeKit::Instance().port_manager->SetPortValue(port::P5DR, result);
}
} // namespace components
} // namespace hinan