// HINAN - simulate H8 microcomputer practice kit
// mainwindow.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/mainwindow.h"
#include "actions.h"
#include "gui/kit_main_ui.h"
#include "practice_kit.h"
#include <QApplication>
#include <QDockWidget>
#include <QLayout>
#include <QMainWindow>
#include <QMimeData>
#include <QPushButton>
#include <QSizePolicy>

namespace hinan {
namespace gui {
MainWindow::MainWindow() {
  setAcceptDrops(true);
  UpdateTitle(PracticeKit::Instance().reader->GetPath());
  setWindowIcon(QIcon(QApplication::applicationDirPath() + "/assets/logo.svg"));
  // Dock
  QDockWidget* port_status = new QDockWidget;
  port_status->setWindowTitle(tr("Status"));
  port_status->setWidget(
      PracticeKit::Instance().components_manager->PortStatusWidget());
  // Central Widget
  KitMainUi* central = new KitMainUi;
  auto policy = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  policy.setHeightForWidth(true);
  central->setSizePolicy(policy);
  // Window
  setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks |
                 QMainWindow::AllowTabbedDocks);
  addDockWidget(Qt::RightDockWidgetArea, port_status);
  resize(800, 600);
  resizeDocks({port_status}, {280}, Qt::Horizontal);
  setCentralWidget(central);
  Actions* actions = new Actions;
  addToolBar(actions->Toolbar());
  setMenuBar(actions->Menubar());

  connect(PracticeKit::Instance().reader, &ProgramReader::PathChangedSignal,
          this, &MainWindow::UpdateTitle);
}
void MainWindow::UpdateTitle(QString path) {
  if (path.isEmpty()) {
    setWindowTitle("HINAN");
  } else {
    setWindowTitle("HINAN - " + path);
  }
}

void MainWindow::closeEvent(QCloseEvent* event) {
  emit CloseSignal();
  QMainWindow::closeEvent(event);
}
void MainWindow::dropEvent(QDropEvent* event) {
  if (event->mimeData()->hasUrls()) {
    PracticeKit::Instance().reader->SetPath(event->mimeData()->urls()[0]);
  }
  QMainWindow::dropEvent(event);
}
} // namespace gui
} // namespace hinan
