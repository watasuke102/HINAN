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
  ProgramReader* reader_;
  PortManager*   manager_;
  QThread*       reader_thread_;
  QThread*       manager_thread_;

 public:
  PracticeKit(QString);
  ~PracticeKit();
  // Operation script
  void ReloadScript();
  void LaunchScript();
  void TerminateScript();
  bool IsScriptActive();
  // Getter
  int          GetPortStat(QString);
  QTreeWidget* PortStatusWidget();

 signals:
  void Launch();
};
} // namespace hinan

#endif // HINAN_PRACTICE_KIT_H_
