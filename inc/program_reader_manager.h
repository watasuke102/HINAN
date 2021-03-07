// HINAN - simulate H8 microcomputer practice kit
// program-reader_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PROGRAM_READER_MANAGER_H_
#define HINAN_PROGRAM_READER_MANAGER_H_

#include "program_reader.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include <QThread>

namespace hinan {
class ProgramReaderManager : public QObject {
  Q_OBJECT
 private:
  ProgramReader* reader_;
  QThread*       reader_thread_;

 public:
  ProgramReaderManager(QString);
  ~ProgramReaderManager();
  void Reload();
  void LaunchScript();
  void TerminateScript();
  int  GetPortStat(const char*);

 public slots:
  void debug() {
    qDebug() << ("**START** (in manager's slot)") << QThread::currentThread();
  }

 signals:
  void Launch();
  void Terminate();
};
} // namespace hinan

#endif // HINAN_PROGRAM_READER_MANAGER_H_
