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
void RemoveCommentAndSpace(QString& text) {
  const QRegExp remove_target[] = {QRegExp("//.*"), QRegExp("[ ]+")};
  for (auto reg_exp : remove_target) {
    if (reg_exp.indexIn(text) != -1) {
      text.remove(reg_exp);
    }
  }
}
bool IsSkipRequired(QString text) {
  const QRegExp skip_target[] = {QRegExp("^\n"), QRegExp("#include.*")};
  for (auto reg_exp : skip_target) {
    if (reg_exp.indexIn(text) != -1) {
      return true;
    }
  }
  return false;
}
CppReader::CppReader(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    qFatal("File cannot open");
    return;
  }
  QString read;
  // Read from file and remove unnecessary part
  while (!file.atEnd()) {
    read = file.readLine();
    RemoveCommentAndSpace(read);
    if (read.isEmpty() || IsSkipRequired(read))
      continue;
    cpp_ += read + '\n';
  }
}

void CppReader::PrintCpp() { qDebug("%s", qUtf8Printable(cpp_)); }
} // namespace hinan
