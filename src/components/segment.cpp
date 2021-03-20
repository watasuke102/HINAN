// HINAN - simulate H8 microcomputer practice kit
// segment.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/segment.h"
#include "port/port.h"
#include "port_manager.h"
#include "practice_kit.h"
#include <QLCDNumber>
#include <QLayout>
#include <QList>
#include <QObject>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
Segment::Segment(QWidget* parent)
    : ComponentInterface(parent, 20, 250, 140, 80) {
  setStyleSheet(
      "QLCDNumber{ border-style: none; color: #ff0123; }"
      "QLCDNumber:disabled{ border-style: none; color: #220123; }");
  QHBoxLayout* layout = new QHBoxLayout();
  segments_.resize(4);
  for (int i = 0; i < segments_.size(); i++) {
    segments_[i] = new QLCDNumber(this);
    segments_[i]->setDigitCount(1);
    segments_[i]->display(0);
    segments_[i]->setEnabled(false);
    layout->addWidget(segments_[i]);
  }
  setLayout(layout);
}
void Segment::Update() {
  const int P4DR  = PracticeKit::Instance().port_manager->Value(port::P4DR);
  const int P4DDR = PracticeKit::Instance().port_manager->Value(port::P4DDR);
  for (int i = 0; i < segments_.size(); i++) {
    int pos = 1 << i;
    // when Data is 1 and Direction is Output(1),
    // Set data's upper 4 bit value to segment
    if ((P4DR & pos) && (P4DDR & pos)) {
      segments_[i]->setEnabled(true);
      segments_[i]->display(P4DR >> 4);
    } else {
      segments_[i]->setEnabled(false);
      segments_[i]->display(0);
    }
  }
}
} // namespace components
} // namespace hinan