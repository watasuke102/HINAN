// HINAN - simulate H8 microcomputer practice kit
// program-reader.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "program_reader.h"
#include "actions.h"
#include "port/port.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QThread>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

void ScriptLog(const asSMessageInfo* msg) {
  qInfo("[Script:%d] %s", msg->row, msg->message);
}

void FileOpen(QFile& file, QString path) {
  file.setFileName(path);
  if (!file.open(QIODevice::ReadOnly))
    qFatal("File cannot open (%s)", path.toUtf8().data());
}

namespace hinan {
ProgramReader::ProgramReader() {
  engine_ = asCreateScriptEngine();
  if (engine_ == 0)
    qFatal("[Failed] Cannot create script engine_");
}
ProgramReader::~ProgramReader() {
  if (!path_.isEmpty()) {
    main_context_->Abort();
    main_context_->Release();
    port_getter_context_->Abort();
    port_getter_context_->Release();
  }
  engine_->ShutDownAndRelease();
  qDebug("Deleted ProgramReader");
}

bool ProgramReader::IsActive() { return isActive_; }

void ProgramReader::SetPath(QUrl url) {
  Terminate();
  path_ = url.toString().remove("file://");
  Load();
}
void ProgramReader::Load() {
  if (path_.isEmpty())
    return;
  QString script = "";
  QFile   file;
  // Open program file and read without include
  FileOpen(file, path_);
  QString read;
  while (!file.atEnd()) {
    read = file.readLine();
    // Skip #include
    if (QRegExp("#include.*").indexIn(read) != -1) {
      continue;
    }
    if (read.isEmpty())
      continue;
    script += read;
  }
  file.close();
  // Open template file and read all
  // if read this first, the error occurs line will be shifted
  FileOpen(file, "assets/template.txt");
  script += file.readAll();
  file.close();
  // Build the script
  CScriptBuilder builder;
  builder.StartNewModule(engine_, "main");
  builder.AddSectionFromMemory("main", script.toUtf8().data());
  engine_->SetMessageCallback(asFUNCTION(ScriptLog), 0, asCALL_CDECL);
  if (builder.BuildModule() < 0) {
    qCritical("[Failed] Cannot build the script");
    path_ = "";
    return;
  }
  // Create context
  main_context_        = engine_->CreateContext();
  port_getter_context_ = engine_->CreateContext();
  qDebug("[Reader] Loaded");
}

void ProgramReader::Terminate() {
  qDebug("[Reader] Terminated");
  isActive_ = false;
  emit DeactivatedSignal();
  if (!path_.isEmpty()) {
    main_context_->Abort();
    port_getter_context_->Abort();
  }
}

void ProgramReader::Run() {
  if (engine_ == 0 || path_.isEmpty()) {
    qCritical("[Failed] Engine is not yet to initialized");
    return;
  }
  qDebug("[Reader] Started");
  isActive_ = true;
  emit             ActivatedSignal();
  asIScriptModule* module = engine_->GetModule("main");

  main_context_->Prepare(module->GetFunctionByDecl("int main()"));
  main_context_->Execute();
  qDebug("[Reader] Finished");
  isActive_ = false;
  emit DeactivatedSignal();
}

// If call this function, please use hinan::port.
// Ex. GetPortStat(hinan::port::P1DDR);
int ProgramReader::GetPortStat(QString port) {
  if (engine_ == 0) {
    qFatal("[Failed] Engine is not yet to initialized");
  }
  asIScriptModule* module = engine_->GetModule("main");

  const QString function_name = QString("int8 Get%1()").arg(port);
  port_getter_context_->Prepare(
      module->GetFunctionByDecl(function_name.toUtf8().data()));
  if (port_getter_context_->Execute() != asEXECUTION_FINISHED) {
    qCritical("[Failed] cannot launch port status get function");
    return -1;
  }
  int result = port_getter_context_->GetReturnDWord();
  return result;
}
} // namespace hinan
