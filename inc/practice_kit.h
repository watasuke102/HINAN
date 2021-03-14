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
  QThread* manager_thread_;
  PracticeKit();

 public:
  ProgramReader* reader;
  PortManager*   manager;

  ~PracticeKit();
  // Operation script
  void ReloadScript();
  void LaunchScript();
  void TerminateScript();
  void StartStopScript();
  // Getter
  int          GetPortStat(QString);
  QTreeWidget* PortStatusWidget();

  static PracticeKit& Instance();

 signals:
  void Launch();
  void StartStop();
};
} // namespace hinan

#endif // HINAN_PRACTICE_KIT_H_
