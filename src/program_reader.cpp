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
#include <angelscript.h>
#include <iostream>
#include <scriptbuilder/scriptbuilder.h>

void ScriptLog(const asSMessageInfo* msg) {
  qInfo("[Script:%d] %s", msg->row, msg->message);
}

namespace hinan {
ProgramReader::ProgramReader(QString path) {
  engine_ = asCreateScriptEngine();
  if (engine_ == 0) {
    qFatal("[Failed] Cannot create script engine_");
    return;
  }
  // Open script file
  builder_.StartNewModule(engine_, "main");
  if (builder_.AddSectionFromFile(path.toUtf8().data()) < 0) {
    qFatal("[Failed] Cannot open script file");
    return;
  }
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
} // namespace hinan
