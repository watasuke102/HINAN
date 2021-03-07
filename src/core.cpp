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
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

void Help() {
  qInfo("usage: ./hinan <option> file_path");
  qInfo(" Options: -h | --help   Show this help message.\n");
}

namespace hinan {
void Core::Run() {
  if (QCoreApplication::arguments().size() < 2) {
    Help();
    QCoreApplication::exit(1);
    return;
  }
  const QStringList argv = QCoreApplication::arguments();
  if (strcmp(argv[1].toUtf8().data(), "--help") == 0 ||
      strcmp(argv[1].toUtf8().data(), "-h") == 0) {
    Help();
    QCoreApplication::exit(0);
    return;
  }
  MainLoop(argv[1]);
  qDebug("===finish===");
  QCoreApplication::exit(0);
}

void Core::MainLoop(QString path) {
  hinan::PracticeKit practice_kit(path);
  QString            line;
  QTextStream        qstdin(stdin);
  while (!qstdin.atEnd()) {
    line = qstdin.readLine();
    if (line == QString("reload")) {
      practice_kit.Reload();
      qDebug("-> Reload Script");
    } else if (line == QString("run")) {
      practice_kit.LaunchScript();
      qDebug("-> Start Script");
    } else if (line == QString("kill") || line == QString("quit")) {
      practice_kit.TerminateScript();
      qDebug("-> killed");
      if (line == QString("quit")) {
        break;
      }
    } else if (line == QString("all")) {
      for (auto str : hinan::port::port_list) {
        int p = practice_kit.GetPortStat(str.toUtf8().data());
        qDebug("%5s: 0x%02x(%d)", str.toUtf8().data(), p, p);
      }
    } else {
      for (auto str : hinan::port::port_list) {
        if (line == str) {
          int p = practice_kit.GetPortStat(line.toUtf8().data());
          qDebug("%5s: 0x%02x(%d)", str.toUtf8().data(), p, p);
          break;
        }
      }
    }
  }
}
} // namespace hinan
