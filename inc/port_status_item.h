// HINAN - simulate H8 microcomputer practice kit
// port_status_item.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PORT_STATUS_ITEM_H_
#define HINAN_PORT_STATUS_ITEM_H_

#include <QObject>
#include <QString>
#include <QTreeWidget>

namespace hinan {
class PortStatusItem : public QObject {
  Q_OBJECT
 private:
  int              value_;
  QString          str_;
  QTreeWidgetItem* item_;

 public:
  PortStatusItem(int, QString, QTreeWidgetItem*);
  QTreeWidgetItem* Item();
  int              Value();
  void             SetValue(int);
  void             UpdateWidget();
};
} // namespace hinan

#endif // HINAN_PORT_STATUS_ITEM_H_