// HINAN - simulate H8 microcomputer practice kit
// port_status_label.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "port_status_label.h"
#include <QString>

namespace hinan {
PortStatusLabel::PortStatusLabel(int x, QString str) : value_(x), str_(str) {
  label_ = new QLabel;
  UpdateLabel();
}
QLabel* PortStatusLabel::Label() { return label_; }
int     PortStatusLabel::Value() { return value_; }
void    PortStatusLabel::SetValue(int x) {
  value_ = x;
  UpdateLabel();
}
void PortStatusLabel::UpdateLabel() {
  QString body = QString::asprintf("%s: 0x%02x", str_.toUtf8().data(), value_);
  label_->setText(body);
}
} // namespace hinan