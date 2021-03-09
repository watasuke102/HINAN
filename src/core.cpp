// HINAN - simulate H8 microcomputer practice kit
// core.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "core.h"
#include "port.h"
#include "practice_kit.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>

void Help() {
  qInfo("usage: ./hinan <option> file_path");
  qInfo(" Options: -h | --help   Show this help message.\n");
}

namespace hinan {
Core::Core() {
  if (QApplication::arguments().size() < 2) {
    Help();
    QApplication::exit(1);
    return;
  }
  const QStringList argv = QApplication::arguments();
  if (argv[1] == QString("--help") || argv[1] == QString("-h")) {
    Help();
    QApplication::exit(0);
    return;
  }
  practice_kit_ = new hinan::PracticeKit(argv[1]);
  // Window
  QMainWindow* main_window = new QMainWindow();
  QWidget*     widget      = new QWidget();
  QVBoxLayout* layout      = practice_kit_->PortStatusLabelList();
  QPushButton* start_stop  = new QPushButton("Start/Stop");
  QPushButton* reload      = new QPushButton("Reload");
  QPushButton* quit        = new QPushButton("Quit");
  layout->addWidget(start_stop);
  layout->addWidget(reload);
  layout->addWidget(quit);
  connect(start_stop, &QPushButton::pressed, this, &Core::StartStop);
  connect(reload, &QPushButton::pressed, practice_kit_, &PracticeKit::ReloadScript);
  connect(quit, &QPushButton::pressed, main_window, &QMainWindow::close);
  connect(quit, &QPushButton::pressed, practice_kit_,
          &PracticeKit::TerminateScript);
  widget->setLayout(layout);
  main_window->setCentralWidget(widget);
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
