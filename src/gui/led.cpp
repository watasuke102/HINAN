// HINAN - simulate H8 microcomputer practice kit
// led.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/led.h"
#include "practice_kit.h"
#include <QLayout>
#include <QList>
#include <QObject>
#include <QPushButton>
#include <QWidget>

namespace hinan {
namespace gui {
LED::LED(QWidget* parent) : QWidget(parent) {
  QHBoxLayout* layout = new QHBoxLayout();
  //layout->setContentsMargins(-1, 0, 1, 0);
  leds_.resize(8);
  for (int i = 7; i >= 0; i--) {
    leds_[i] = new QPushButton(QString::number(i), this);
    // leds_[i]->setFlat(true);
    // leds_[i]->setEnabled(false);
    layout->addWidget(leds_[i]);
  }
  setLayout(layout);
  // set background color
}
} // namespace gui
} // namespace hinan