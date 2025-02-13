// HINAN - simulate H8 microcomputer practice kit
// core.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_CORE_H_
#define HINAN_CORE_H_

#include "gui/mainwindow.h"
#include <QObject>

namespace hinan {
class Core : public QObject {
  Q_OBJECT
 private:
  gui::MainWindow* main_window_;

 public:
  Core();
  void SetupMainWindow();

  static void AboutDialog();
  static void ErrorDialog(QString);
  static void ErrorDialog(QString, QString);
  static void InfoDialog(QString);
  static void InfoDialog(QString, QString);
  static int  YesNoDialog(QString);
  static int  YesNoDialog(QString, QString);
};
} // namespace hinan

#endif // HINAN_CORE_H_