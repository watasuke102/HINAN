// HINAN - simulate H8 microcomputer practice kit
// main.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "port.h"
#include "program_reader.h"
#include <QDebug>
#include <QTextStream>

void Help() {
  qInfo("usage: ./hinan <option>");
  qInfo(" Options: -h | --help   Show this help message.\n");
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    Help();
    return 1;
  }
  if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
    Help();
    return 0;
  }
  hinan::ProgramReaderManager manager(argv[1]);
  QString                     line;
  QTextStream                 qstdin(stdin);
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
      qDebug("-> 0x%02x", manager.GetPortStat(line.toUtf8().data()));
    }
  }
  qDebug("-> finish");
  return 0;
}
