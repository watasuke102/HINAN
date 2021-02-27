// HINAN - simulate H8 microcomputer practice kit
// cpp-reader.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "cpp_reader.h"
#include <QDebug>
#include <QFile>
#include <QString>

namespace hinan {
bool IncludingTextByRegExp(QString target, QRegExp reg_exp) {
  if (reg_exp.indexIn(target) != -1)
    return true;
  return false;
}
CppReader::CppReader(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File cannot open";
    return;
  }
  // Remove comments and includes
  QString       read;
  const QRegExp include("#include.*");
  const QRegExp line_comment("//.*");
  while (!file.atEnd()) {
    read = file.readLine();
    qDebug() << "[debug] read(before) = 「" + read + "」";
    if (read == "\n" || read == "" || IncludingTextByRegExp(read, include)) {
      qDebug() << "!!ignored";
      continue;
    }
    if (IncludingTextByRegExp(read, line_comment)) {
      read.remove(line_comment);
    }
    qDebug() << "[debug] read(after)  = 「" + read + "」";
    cpp_ += read + '\n';
  }
}

void CppReader::PrintCpp() { qDebug() << cpp_; }
} // namespace hinan
