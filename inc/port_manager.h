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

#include "port/port.h"
#include "port_status_item.h"
#include "program_reader.h"
#include <QLayout>
#include <QMap>
#include <QObject>
#include <QString>
#include <QTreeWidget>

namespace hinan {
class PortManager : public QObject {
  Q_OBJECT
 private:
  QMap<QString, PortStatusItem*> map_;
  QTreeWidget*                   widget_;
  bool                           isTerminated_;

 public:
  PortManager();
  ~PortManager();
  void         Update();
  int          GetPortValue(QString);
  void         SetPortValue(QString, unsigned char);
  QTreeWidget* PortStatusWidget();

 public slots:
  void Run();
  void Terminate();
};
} // namespace hinan

#endif // HINAN_PORT_MANAGER_H_