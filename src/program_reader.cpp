// HINAN - simulate H8 microcomputer practice kit
// program_reader.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "program_reader.h"
#include "actions.h"
#include "port/port.h"
#include "practice_kit.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QThread>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

void ScriptLog(const asSMessageInfo* msg) {
  qInfo("[Script:%d] %s", msg->row, msg->message);
}

namespace hinan {
ProgramReader::ProgramReader() {
  engine_ = asCreateScriptEngine();
  if (engine_ == 0)
    qFatal("[Failed] Cannot create script engine");
  QString function_name("int %1");
  int     r;
  for (auto str : port::port_list) {
    map_.insert(str, 0);
    r = engine_->RegisterGlobalProperty(function_name.arg(str).toUtf8().data(),
                                        &map_[str]);
    if (r < 0) {
      qFatal("Failed to register property: %s", str);
    }
  }
}
ProgramReader::~ProgramReader() {
  if (!path_.isEmpty()) {
    main_context_->Abort();
    main_context_->Release();
    port_getter_context_->Abort();
    port_getter_context_->Release();
    port_setter_context_->Abort();
    port_setter_context_->Release();
  }
  engine_->ShutDownAndRelease();
  qDebug("Deleted ProgramReader");
}

bool ProgramReader::IsActive() { return isActive_; }

QString ProgramReader::GetPath() { return path_; }

void ProgramReader::SetPath(QUrl url) {
  Terminate();
  path_ = url.toString().remove("file://");
  emit PathChangedSignal(path_);
  Load();
}

void ProgramReader::Reload() {
  if (path_.isEmpty())
    return;
  Terminate();
  Load();
}

void ProgramReader::Load() {
  if (path_.isEmpty())
    return;
  QString script = "";
  QFile   file;
  // Open program file and read without include
  file.setFileName(path_);
  if (!file.open(QIODevice::ReadOnly))
    qFatal("File cannot open (%s)", path_.toUtf8().data());
  QString read;
  while (!file.atEnd()) {
    read = file.readLine();
    // Skip #include
    if (QRegExp("#include.*").indexIn(read) != -1) {
      continue;
    }
    // Replace while(1) => while(true)
    // AngelScript only allows boolean type expression
    read.replace(QRegExp("while *\\(1\\)"), "while(true)");
    if (read.isEmpty())
      continue;
    script += read;
  }
  file.close();
  // Build the script
  CScriptBuilder builder;
  builder.StartNewModule(engine_, "main");
  builder.AddSectionFromMemory("main", script.toUtf8().data());
  engine_->SetMessageCallback(asFUNCTION(ScriptLog), 0, asCALL_CDECL);
  if (builder.BuildModule() < 0) {
    emit ErrorSignal(&staticMetaObject, tr("Cannot build the script"));
    path_ = "";
    emit PathChangedSignal(path_);
    return;
  }
  // Create context
  main_context_        = engine_->CreateContext();
  port_getter_context_ = engine_->CreateContext();
  port_setter_context_ = engine_->CreateContext();
  qDebug("[Reader] Loaded");
}

void ProgramReader::Terminate() {
  qDebug("[Reader] Terminated");
  isActive_ = false;
  emit DeactivatedSignal();
  if (!path_.isEmpty()) {
    main_context_->Abort();
    port_getter_context_->Abort();
    port_getter_context_->Release();
    port_getter_context_ = engine_->CreateContext();
    port_setter_context_->Abort();
    port_setter_context_->Release();
    port_setter_context_ = engine_->CreateContext();
  }
}

void ProgramReader::Run() {
  if (engine_ == 0 || path_.isEmpty()) {
    emit ErrorSignal(&staticMetaObject, tr("Engine is not yet to initialized"));
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

// If call these function, please use hinan::port.
// Ex. GetPortValue(hinan::port::P1DDR);
//     SetPortValue(hinan::port::P2DR, 0x0f);
int ProgramReader::GetPortValue(QString port) { return map_[port]; }

void ProgramReader::SetPortValue(QString port, unsigned char value) {
  map_[port] = value;
}
} // namespace hinan
