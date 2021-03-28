// HINAN - simulate H8 microcomputer practice kit
// core.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "core.h"
#include "gui/mainwindow.h"
#include "port/port.h"
#include "practice_kit.h"
#include "update_checker.h"
#include <QApplication>
#include <QDebug>
#include <QEventLoop>
#include <QMessageBox>
#include <QObject>
#include <QSplashScreen>
#include <QTimer>

namespace hinan {
Core::Core() {
  QString           path;
  const QStringList argv = QApplication::arguments();
  if (QApplication::arguments().size() >= 2) {
    if (argv[1] == QString("--help") || argv[1] == QString("-h")) {
      qInfo("usage: ./hinan <option> file_path");
      qInfo(" Options: -h | --help   Show this help message.\n");
      exit(0);
      return;
    } else {
      path = argv[1];
    }
  }
  main_window_ = new gui::MainWindow();
  // Connect
  connect(main_window_, &gui::MainWindow::CloseSignal, &PracticeKit::Instance(),
          &PracticeKit::TerminateScript);
  connect(PracticeKit::Instance().reader, &ProgramReader::ErrorSignal, this,
          &Core::Error);
  PracticeKit::Instance().reader->SetPath(path);

  // Splash screen
  QPixmap pixmap =
      QIcon(QApplication::applicationDirPath() + "/assets/logo.svg")
          .pixmap(QSize(250, 250));
  QSplashScreen splash(pixmap);
  splash.setWindowFlag(Qt::WindowStaysOnTopHint, false);
  splash.show();
  QApplication::processEvents();

  // Check for update
  splash.showMessage(tr("Checking for update..."));
  UpdateChecker checker(false);
  QTimer        timer;
  timer.setSingleShot(true);
  QEventLoop loop;
  connect(&checker, &UpdateChecker::FinishedSignal, &loop, &QEventLoop::quit);
  connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
  // 10 sec for timeout
  timer.start(10000);

  checker.Check();
  loop.exec();

  // Wait to show splash screen
  splash.showMessage(tr("Loading..."));
  QThread::msleep(1500);
  QApplication::processEvents();

  // End of splash screen
  main_window_->show();
  splash.finish(main_window_);
}

void Core::Error(const QMetaObject* obj, QString body) {
  qCritical("[%s] Error: %s", obj->className(), body.toUtf8().data());
  QMessageBox::critical(main_window_, tr("Error"), body);
}
} // namespace hinan
