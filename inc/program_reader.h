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
  QMap<QString, unsigned char> map_;

  bool              isActive_ = false;
  QString           path_;
  asIScriptEngine*  engine_;
  asIScriptContext* main_context_;
  asIScriptContext* port_getter_context_;
  asIScriptContext* port_setter_context_;

 public:
  ProgramReader();
  ~ProgramReader();
  bool    IsActive();
  void    SetPath(QUrl);
  void    Load();
  QString GetPath();

  int  GetPortValue(QString);
  void SetPortValue(QString, unsigned char);

 public slots:
  void Run();
  void Reload();
  void Terminate();

 signals:
  void ActivatedSignal();
  void DeactivatedSignal();
  void PathChangedSignal(QString);
  void ErrorSignal(QString);
};
} // namespace hinan

#endif // HINAN_PROGRAM_READER_H_
