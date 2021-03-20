// HINAN - simulate H8 microcomputer practice kit
// practice_kit.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PRACTICE_KIT_H_
#define HINAN_PRACTICE_KIT_H_

#include "components_manager.h"
#include "port_manager.h"
#include "program_reader.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include <QThread>
#include <QTreeWidget>

namespace hinan {
class PracticeKit : public QObject {
  Q_OBJECT
 private:
  QThread* reader_thread_;
  QThread* port_manager_thread_;
  QThread* components_manager_thread_;
  PracticeKit();

 public:
  ProgramReader*     reader;
  PortManager*       port_manager;
  ComponentsManager* components_manager;

  ~PracticeKit();
  void StartStopScript();
  void TerminateScript();
  void ReloadScript();

  static PracticeKit& Instance();

 signals:
  void LaunchSignal();
  void StartStopSignal();
  void ResizeComponentsSignal(QSize, double);
};
} // namespace hinan

#endif // HINAN_PRACTICE_KIT_H_
