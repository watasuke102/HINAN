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
#include "program_reader.h"
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

void Help() {
  qInfo("usage: ./hinan <option>");
  qInfo(" Options: -h | --help   Show this help message.\n");
}

namespace hinan {
void Core::Run() {
  if (QCoreApplication::arguments().size() < 2) {
    Help();
    QCoreApplication::exit(1);
  }
  const QStringList argv = QCoreApplication::arguments();
  if (strcmp(argv[1].toUtf8().data(), "--help") == 0 ||
      strcmp(argv[1].toUtf8().data(), "-h") == 0) {
    Help();
    QCoreApplication::exit(0);
  }
  hinan::ProgramReaderManager manager(argv[1]);
  QString                     line;
  QTextStream                 qstdin(stdin);
  // manager.LaunchScript();
  while (!qstdin.atEnd()) {
    line = qstdin.readLine();
    if (line == QString("run")) {
      qDebug("-> Start Script");
      manager.LaunchScript();
    } else if (line == QString("kill") || line == QString("quit")) {
      qDebug("-> killed");
      manager.FinishScript();
      if (line == QString("quit")) {
        break;
      }
    } else {
      int p = manager.GetPortStat(line.toUtf8().data());
      qDebug("-> 0x%02x(%d)", p, p);
    }
  }
  qDebug("===finish===");
}
} // namespace hinan