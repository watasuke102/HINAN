// HINAN - simulate H8 microcomputer practice kit
// main.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "core.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  hinan::Core* core = new hinan::Core();
  QTimer::singleShot(0, core, SLOT(Run()));
  return app.exec();
}
/*
int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  hinan::Core* core = new hinan::Core();
  auto         w    = core->MainWindow();
  w->show();
  QThread* main_thread = new QThread();
  QObject::connect(main_thread, &QThread::started, core, &hinan::Core::Run);
  main_thread->start();
  return app.exec();
}
*/
