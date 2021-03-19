// HINAN - simulate H8 microcomputer practice kit
// core.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "core.h"
#include "gui/mainwindow.h"
#include "port/port.h"
#include "practice_kit.h"
#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>

void Help() {
  qInfo("usage: ./hinan <option> file_path");
  qInfo(" Options: -h | --help   Show this help message.\n");
}

namespace hinan {
Core::Core() {
  QString           path;
  const QStringList argv = QApplication::arguments();
  if (QApplication::arguments().size() >= 2) {
    if (argv[1] == QString("--help") || argv[1] == QString("-h")) {
      Help();
      QApplication::exit(0);
      return;
    } else {
      path = argv[1];
    }
  }
  main_window_ =
      new gui::MainWindow(PracticeKit::Instance().PortStatusWidget());
  // Connect
  connect(main_window_, &gui::MainWindow::CloseSignal, &PracticeKit::Instance(),
          &PracticeKit::TerminateScript);
  connect(PracticeKit::Instance().reader, &ProgramReader::ErrorSignal, this,
          &Core::Error);

  PracticeKit::Instance().reader->SetPath(path);

  main_window_->show();
}

void Core::Error(const QMetaObject* obj, QString body) {
  qCritical("[%s] Error: %s", obj->className(), body.toUtf8().data());
  QMessageBox::critical(main_window_, tr("Error"), body);
}
} // namespace hinan
