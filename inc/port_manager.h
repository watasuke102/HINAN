// HINAN - simulate H8 microcomputer practice kit
// port_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PORT_MANAGER_H_
#define HINAN_PORT_MANAGER_H_

#include "port.h"
#include "program_reader.h"
#include <QLabel>
#include <QLayout>
#include <QList>
#include <QMap>
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
  PortStatusLabel(int x, QString str) : value_(x), str_(str) {
    label_ = new QLabel;
    UpdateLabel();
  }
  QLabel* Label() { return label_; }
  int     Value() { return value_; }
  void    SetValue(int x) {
    value_ = x;
    UpdateLabel();
  }
  void UpdateLabel() {
    QString body = QString::asprintf("%s: %04x", str_.toUtf8().data(), value_);
    label_->setText(body);
  }
};

class PortManager : public QObject {
  Q_OBJECT
 private:
  QMap<QString, PortStatusLabel*> map_;
  ProgramReader*                  reader_;
  QVBoxLayout*                    label_list_;

 public:
  PortManager(ProgramReader*);
  int          Value(QString);
  void         Update();
  QVBoxLayout* PortStatusLabelList(QString);
 public slots:
  void Run();
};
} // namespace hinan

#endif // HINAN_PORT_MANAGER_H_