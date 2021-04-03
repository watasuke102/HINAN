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
#include "setting_manager.h"
#include "update_checker.h"
#include <QApplication>
#include <QDebug>
#include <QEventLoop>
#include <QMessageBox>
#include <QObject>
#include <QSplashScreen>
#include <QTimer>

namespace hinan {
Core::Core() : main_window_(new gui::MainWindow) {
  // Connect
  connect(main_window_, &gui::MainWindow::CloseSignal, &PracticeKit::Instance(),
          &PracticeKit::TerminateScript);
  connect(PracticeKit::Instance().reader, &ProgramReader::ErrorSignal,
          [=](QString body) { ErrorDialog(body); });
}

void Core::SetupMainWindow() {
  // Splash screen
  // svg size is 450x200, but it will be displayed in a smaller size
  QPixmap       pixmap = QIcon(":/assets/splash.svg").pixmap(QSize(500, 250));
  QSplashScreen splash(QApplication::screens().at(0), pixmap);
  int           pos = Qt::AlignRight | Qt::AlignBottom;
  splash.setWindowFlag(Qt::WindowStaysOnTopHint, false);
  {
    const QString show_splash =
        SettingManager::Instance().GetValue(SettingManager::ShowSplashScreen);
    if (show_splash != QString("false")) {
      splash.show();
    }
  }
  QApplication::processEvents();

  splash.showMessage(tr("Initializing settings..."), pos);
  QApplication::processEvents();

  // Check for update
  {
    QString check_update = SettingManager::Instance().GetValue(
        SettingManager::CheckUpdateWhenStartup);
    if (check_update != QString("false")) {
      int timeout;
      {
        bool ok;
        timeout = SettingManager::Instance()
                      .GetValue(SettingManager::CheckUpdateTimeOut)
                      .toInt(&ok);
        if (!ok) {
          // 10 second
          timeout = 10000;
        }
      }
      splash.showMessage(tr("Checking for update..."), pos);
      UpdateChecker checker(false);
      QTimer        timer;
      timer.setSingleShot(true);
      QEventLoop loop;
      connect(&checker, &UpdateChecker::FinishedSignal, &loop,
              &QEventLoop::quit);
      connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
      timer.start(timeout);

      checker.Check();
      loop.exec();
    }
  }

  // Wait to show splash screen
  splash.showMessage(tr("Loading..."), pos);
  QThread::msleep(1500);
  QApplication::processEvents();

  // End of splash screen
  main_window_->show();
  splash.finish(main_window_);
}

void Core::AboutDialog() {
  QString body =
      tr("<h1>HINAN - v%1</h1>"
         "<h3>HINAN Is Not AN emulator</h3>"
         "<hr>"
         "<p>This software is released under the Mozilla Public "
         "License Version 2.0. <br>"
         "This license permissions modification, distribution, "
         "patent/commercial/private use. <br>"
         "When you exploit this software, you must notice about License "
         "and Copyright, disclose source, and include original. <br>"
         "An 'exploit' as is defined here is not only using software, but also "
         "modification, distributing, or include to your production. </p>"
         "<p> HINAN's source code is diclosed "
         "<a href='https://github.com/watasuke102/HINAN'>here</a>. "
         "If you find any bug or dissatisfaction, please report.</p>")
          .arg(QApplication::applicationVersion());
  QMessageBox* box = new QMessageBox;
  box->setWindowTitle(tr("Version"));
  box->setText(body);
  QIcon icon(":/assets/logo.svg");
  box->setIconPixmap(icon.pixmap(100, 100));
  box->show();
}

void Core::ErrorDialog(QString body) { ErrorDialog(body, ""); }
void Core::ErrorDialog(QString body, QString detail) {
  QMessageBox* box = new QMessageBox;
  box->setWindowIcon(QIcon(":/assets/logo.svg"));
  box->setIconPixmap(QIcon(":/assets/icon/error.svg").pixmap(50, 50));
  box->setWindowTitle(tr("Error"));
  box->setText(body);
  if (!detail.isEmpty()) {
    box->setDetailedText(detail);
  }
  qCritical("Error: %s", body.toUtf8().data());
  box->show();
}

void Core::InfoDialog(QString body) { InfoDialog(body, ""); }
void Core::InfoDialog(QString body, QString detail) {
  QMessageBox* box = new QMessageBox;
  box->setWindowIcon(QIcon(":/assets/logo.svg"));
  box->setIconPixmap(QIcon(":/assets/icon/info.svg").pixmap(50, 50));
  box->setWindowTitle(tr("Info"));
  box->setText(body);
  if (!detail.isEmpty()) {
    box->setDetailedText(detail);
  }
  qInfo("Info: %s", body.toUtf8().data());
  box->show();
}

} // namespace hinan
