// HINAN - simulate H8 microcomputer practice kit
// program-reader.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PROGRAM_READER_H_
#define HINAN_PROGRAM_READER_H_

#include <QDebug>
#include <QObject>
#include <QString>
#include <QThread>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

namespace hinan {
class ProgramReader : public QObject {
  Q_OBJECT
 private:
  QString           path_;
  asIScriptEngine*  engine_;
  asIScriptContext* main_context_;
  asIScriptContext* port_getter_context_;

 public:
  ProgramReader(QString);
  ~ProgramReader();
  int  GetPortStat(const char*);
  void Load();

 public slots:
  void Run();
  void Terminate();
};

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

#endif // HINAN_PROGRAM_READER_H_
