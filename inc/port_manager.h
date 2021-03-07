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
#include <QMap>
#include <QObject>
#include <QString>

namespace hinan {
class PortManager : public QObject {
  Q_OBJECT
 private:
  QMap<QString, int> map_;
  ProgramReader*     reader_;

 public:
  PortManager(ProgramReader*);
  int  Value(QString);
  void Update();
 public slots:
  void Run();
};
} // namespace hinan

#endif // HINAN_PORT_MANAGER_H_