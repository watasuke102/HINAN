// HINAN - simulate H8 microcomputer practice kit
// program-reader.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "program_reader.h"
#include "port.h"
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
// Reader
ProgramReader::ProgramReader(QString path) : path_(path) { Load(); }
ProgramReader::~ProgramReader() {
  main_context_->Abort();
  port_getter_context_->Abort();
  engine_->ShutDownAndRelease();
}

void ProgramReader::Load() {
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
  // AngelScript Engine
  engine_ = asCreateScriptEngine();
  if (engine_ == 0) {
    qFatal("[Failed] Cannot create script engine_");
    return;
  }
  // Build the script
  CScriptBuilder builder;
  builder.StartNewModule(engine_, "main");
  builder.AddSectionFromMemory("main", script.toUtf8().data());
  engine_->SetMessageCallback(asFUNCTION(ScriptLog), 0, asCALL_CDECL);
  if (builder.BuildModule() < 0) {
    qFatal("[Failed] Cannot build the script");
    return;
  }
  // Create context
  main_context_        = engine_->CreateContext();
  port_getter_context_ = engine_->CreateContext();
}
ProgramReader::~ProgramReader() { engine_->ShutDownAndRelease(); }

void ProgramReader::Run() {
  if (engine_ == 0) {
    qFatal("[Failed] Engine is not yet to initialized");
  }
  qDebug() << ("---START Reader::Run()---") << QThread::currentThread();
  asIScriptModule* module = engine_->GetModule("main");

  main_context_->Prepare(module->GetFunctionByDecl("int main()"));
  main_context_->Execute();
  main_context_->Release();
  qDebug("---FINISH Reader::Run()---");
}

// If call this function, please use hinan::port.
// Ex. GetPortStat(hinan::port::P1DDR);
int ProgramReader::GetPortStat(const char* port) {
  if (engine_ == 0) {
    qFatal("[Failed] Engine is not yet to initialized");
  }
  asIScriptModule* module = engine_->GetModule("main");

  const QString function_name = QString("int16 Get%1()").arg(port);
  port_getter_context_->Prepare(
      module->GetFunctionByDecl(function_name.toUtf8().data()));
  if (port_getter_context_->Execute() != asEXECUTION_FINISHED) {
    qCritical("[Failed] cannot launch port status get function");
    port_getter_context_->Release();
    return -1;
  }
  int result = port_getter_context_->GetReturnDWord();
  port_getter_context_->Release();
  return result;
}

// Manager
ProgramReaderManager::ProgramReaderManager(QString path) {
  reader_thread_ = new QThread(this);
  reader_        = new ProgramReader(path);
  reader_->moveToThread(reader_thread_);
  // When called this->LaunchScript(), call reader_->Run()
  connect(this, SIGNAL(LaunchScriptSignal()), reader_, SLOT(Run()));
  connect(this, SIGNAL(LaunchScriptSignal()), this, SLOT(debug()));
  reader_thread_->start();
}
ProgramReaderManager::~ProgramReaderManager() {
  reader_thread_->quit();
  reader_thread_->wait();
}

void ProgramReaderManager::Reload() { reader_->Load(); }
  reader_thread_->quit();
  reader_thread_->wait();
}
int ProgramReaderManager::GetPortStat(const char* port) {
  return reader_->GetPortStat(port);
}
} // namespace hinan
