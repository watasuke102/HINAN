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
#include "port.h"
#include "practice_kit.h"
#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QMainWindow>
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
  if (QApplication::arguments().size() > 2) {
    if (argv[1] == QString("--help") || argv[1] == QString("-h")) {
      Help();
      QApplication::exit(0);
      return;
    }
    path = argv[1];
  }
  practice_kit_    = new PracticeKit(path);
  auto main_window = new gui::MainWindow(practice_kit_->PortStatusWidget());
  // Connect
  connect(main_window, &gui::MainWindow::StartStop, this, &Core::StartStop);
  connect(main_window, &gui::MainWindow::Reload, practice_kit_,
          &PracticeKit::ReloadScript);
  connect(main_window, &gui::MainWindow::Close, practice_kit_,
          &PracticeKit::TerminateScript);
  connect(main_window, &gui::MainWindow::Opened, practice_kit_,
          &PracticeKit::Opened);

  main_window->show();
}

void Core::StartStop() {
  if (practice_kit_->IsScriptActive()) {
    practice_kit_->TerminateScript();
    qDebug("Script terminated");
  } else {
    practice_kit_->LaunchScript();
    qDebug("Script started");
  }
}
} // namespace hinan
