// HINAN - simulate H8 microcomputer practice kit
// program-reader.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "program_reader.h"
#include <QDebug>
#include <QDir>
#include <QFile>
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
ProgramReader::ProgramReader(QString path) {
  QString script = "";
  QFile   file;
  // Open program file and read without include
  FileOpen(file, path);
  QString read;
  // Read from file and remove unnecessary part
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
  FileOpen(file, "assets/template.txt");
  script += file.readAll();
  file.close();
  // AngelScript Engine
  engine_ = asCreateScriptEngine();
  if (engine_ == 0) {
    qFatal("[Failed] Cannot create script engine_");
    return;
  }
  builder_.StartNewModule(engine_, "main");
  builder_.AddSectionFromMemory("main", script.toUtf8().data());
  engine_->SetMessageCallback(asFUNCTION(ScriptLog), 0, asCALL_CDECL);
  if (builder_.BuildModule() < 0) {
    qFatal("[Failed] Cannot build the script");
    return;
  }
}
ProgramReader::~ProgramReader() { engine_->ShutDownAndRelease(); }

void ProgramReader::Run() {
  if (engine_ == 0) {
    qFatal("[Failed] Engine is not yet to initialized");
  }
  asIScriptModule*  module  = engine_->GetModule("main");
  asIScriptContext* context = engine_->CreateContext();

  context->Prepare(module->GetFunctionByDecl("int main()"));
  context->Execute();

  context->Release();
}
int ProgramReader::GetPortStat(const char* port) {
  if (engine_ == 0) {
    qFatal("[Failed] Engine is not yet to initialized");
  }
  asIScriptModule*  module  = engine_->GetModule("main");
  asIScriptContext* context = engine_->CreateContext();

  const QString function_name = QString("int16 Get%1()").arg(port);
  context->Prepare(module->GetFunctionByDecl(function_name.toUtf8().data()));
  if (context->Execute() != asEXECUTION_FINISHED) {
    qCritical("[Failed] cannot launch port status get function");
    context->Release();
    return -1;
  }
  int result = context->GetReturnDWord();
  context->Release();
  return result;
}
} // namespace hinan
