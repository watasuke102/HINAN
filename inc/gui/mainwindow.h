// HINAN - simulate H8 microcomputer practice kit
// mainwindow.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_MAINWINDOW_H_
#define HINAN_MAINWINDOW_H_

#include <QCloseEvent>
#include <QMainWindow>
#include <QObject>
#include <QString>

namespace hinan {
namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget*);
  void closeEvent(QCloseEvent*);
  void UpdateTitle(QString);

 signals:
  void CloseSignal();
};
} // namespace gui
} // namespace hinan

#endif // HINAN_MAINWINDOW_H_