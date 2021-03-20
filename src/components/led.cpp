// HINAN - simulate H8 microcomputer practice kit
// led.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/led.h"
#include "practice_kit.h"
#include <QLayout>
#include <QList>
#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
LED::LED(QWidget* parent) : ComponentInterface(parent, 68, 150, 100, 30) {
  setStyleSheet(
      "QPushButton{ background-color: #220123; }"
      "QPushButton:checked{ background-color: #ff0123; }");
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setSpacing(2);
  leds_.resize(8);
  for (int i = 7; i >= 0; i--) {
    leds_[i] = new QPushButton(this);
    // leds_[i]->setFlat(true);
    // leds_[i]->setEnabled(false);
    leds_[i]->setCheckable(true);
    layout->addWidget(leds_[i]);
  }
  setLayout(layout);
  // set background color
}
void LED::Update() {}
} // namespace components
} // namespace hinan