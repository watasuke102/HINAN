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
  hinan::ProgramReader reader(argv[1]);
  reader.Run();
  qDebug() << reader.GetPortStat(hinan::port::P4DDR);
  qDebug() << reader.GetPortStat(hinan::port::PBDR);
  return 0;
}
