// HINAN - simulate H8 microcomputer practice kit
// port_status_label.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PORT_STATUS_LABEL_H_
#define HINAN_PORT_STATUS_LABEL_H_

#include <QLabel>
#include <QObject>
#include <QString>

namespace hinan {
class PortStatusLabel : public QObject {
  Q_OBJECT
 private:
  int     value_;
  QLabel* label_;
  QString str_;

 public:
  PortStatusLabel(int, QString);
  QLabel* Label();
  int     Value();
  void    SetValue(int);
  void    UpdateLabel();
};
} // namespace hinan

#endif // HINAN_PORT_STATUS_LABEL_H_