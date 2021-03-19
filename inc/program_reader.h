// HINAN - simulate H8 microcomputer practice kit
// program_reader.h
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
#include <QUrl>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

namespace hinan {
class ProgramReader : public QObject {
  Q_OBJECT
 private:
  bool              isActive_ = false;
  QString           path_;
  asIScriptEngine*  engine_;
  asIScriptContext* main_context_;
  asIScriptContext* port_getter_context_;

 public:
  ProgramReader();
  ~ProgramReader();
  bool IsActive();
  int  GetPortStat(QString);
  void SetPath(QUrl);
  void Load();
  QString GetPath();

 public slots:
  void Run();
  void Terminate();

 signals:
  void ActivatedSignal();
  void DeactivatedSignal();
  void PathChangedSignal(QString);
  void ErrorSignal(const QMetaObject*, QString);
};
} // namespace hinan

#endif // HINAN_PROGRAM_READER_H_
