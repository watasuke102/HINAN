// HINAN - simulate H8 microcomputer practice kit
// main.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <QDebug>
#include <string.h>

void Help() {
  qDebug() << "usage: ./hinan <option>";
  qDebug() << " Options: -h | --help   Show this help message.";
  qDebug() << "\n";
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    Help();
    return 1;
  }
  if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")) {
    Help();
    return 0;
  }
  qDebug() << argv[1];
  return 0;
}
