// HINAN - simulate H8 microcomputer practice kit
// cpp-reader.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_CPP_READER_H_
#define HINAN_CPP_READER_H_

#include <QFile>
#include <QString>

namespace hinan {
class CppReader {
 private:
  QString cpp_;

 public:
  CppReader(QString);
  void PrintCpp();
};
} // namespace hinan

#endif // HINAN_CPP_READER_H_
