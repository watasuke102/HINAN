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
  QMainWindow* main_window = new QMainWindow();
  practice_kit_             = new hinan::PracticeKit(argv[1]);
  QWidget*     widget       = new QWidget();
  QVBoxLayout* layout       = practice_kit_->PortStatusLabelList("all");
  layout->addWidget(new QPushButton("TEST"));
  widget->setLayout(layout);
  main_window->setCentralWidget(widget);
  main_window->show();
}
void Core::Run() {
  practice_kit_->LaunchScript();

  /**
  QString     line;
  QTextStream qstdin(stdin);
  while (!qstdin.atEnd()) {
    line = qstdin.readLine();
    if (line == QString("reload")) {
      practice_kit_->ReloadScript();
      qDebug("-> Reload Script");
    } else if (line == QString("run")) {
      practice_kit_->LaunchScript();
      qDebug("-> Start Script");
    } else if (line == QString("kill") || line == QString("quit")) {
      practice_kit_->TerminateScript();
      qDebug("-> killed");
      if (line == QString("quit")) {
        break;
      }
    } else if (line == QString("all")) {
      for (auto str : hinan::port::port_list) {
        int p = practice_kit_->GetPortStat(str.toUtf8().data());
        qDebug("%5s: 0x%02x(%d)", str.toUtf8().data(), p, p);
      }
    } else {
      for (auto str : hinan::port::port_list) {
        if (line == str) {
          int p = practice_kit_->GetPortStat(line.toUtf8().data());
          qDebug("%5s: 0x%02x(%d)", line.toUtf8().data(), p, p);
          break;
        }
      }
    }
  }
  /**/
  qDebug("===finish===");
  // QApplication::exit(0);
}
} // namespace hinan
