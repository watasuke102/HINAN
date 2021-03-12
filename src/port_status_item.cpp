// HINAN - simulate H8 microcomputer practice kit
// port_status_item.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "port_status_item.h"
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QTreeWidget>
namespace hinan {
PortStatusItem::PortStatusItem(int x, QString str, QTreeWidgetItem* item)
    : value_(x), str_(str), item_(item) {
  item_->setText(0, str);
  UpdateWidget();
}
QTreeWidgetItem* PortStatusItem::Item() { return item_; }
int              PortStatusItem::Value() { return value_; }
void             PortStatusItem::SetValue(int x) {
  value_ = x;
  UpdateWidget();
}
void PortStatusItem::UpdateWidget() {
  QString hex = QString::asprintf("0x%02x", value_);
  // convert DEC->BIN (Ex. 13->1101)
  QString bin = "";
  int     val = value_;
  for (int i = 0; i < 8; i++) {
    bin += QString::number((val >> i) & 1);
  }
  std::reverse(bin.begin(), bin.end());
  item_->setText(1, hex);
  item_->setText(2, bin);
  item_->setText(3, QString::number(value_));
}
} // namespace hinan