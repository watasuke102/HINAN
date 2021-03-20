// HINAN - simulate H8 microcomputer practice kit
// led.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/led.h"
#include "port/port.h"
#include "port_manager.h"
#include "practice_kit.h"
#include <QLayout>
#include <QList>
#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
LED::LED(QWidget* parent) : ComponentInterface(parent, 63, 155, 95, 30) {
  setStyleSheet(
      "QPushButton{ background-color: #220123; }"
      "QPushButton:checked{ background-color: #ff0123; }");
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setSpacing(2);
  leds_.resize(8);
  for (int i = leds_.size() - 1; i >= 0; i--) {
    leds_[i] = new QPushButton(this);
    leds_[i]->setEnabled(false);
    leds_[i]->setCheckable(true);
    layout->addWidget(leds_[i]);
  }
  setLayout(layout);
}
void LED::Update() {
  const int PBDR =
      PracticeKit::Instance().port_manager->GetPortValue(port::PBDR);
  const int PBDDR =
      PracticeKit::Instance().port_manager->GetPortValue(port::PBDDR);
  for (int i = leds_.size() - 1; i >= 0; i--) {
    int pos = 1 << i;
    // when Data is 0 and Direction is Output(1),
    // Turn on the LED
    leds_[i]->setChecked(!(PBDR & pos) && (PBDDR & pos));
  }
}
} // namespace components
} // namespace hinan