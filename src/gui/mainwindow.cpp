// HINAN - simulate H8 microcomputer practice kit
// mainwindow.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/mainwindow.h"
#include <QDockWidget>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>

namespace hinan {
namespace gui {
MainWindow::MainWindow(QLayout* main_layout) {
  // Dock
  QWidget* dock = new QWidget;
  dock->setLayout(main_layout);
  QDockWidget* port_status = new QDockWidget;
  port_status->setWidget(dock);
  // Central Widget
  QWidget*     central    = new QWidget;
  QVBoxLayout* layout     = new QVBoxLayout;
  QPushButton* start_stop = new QPushButton("Start/Stop");
  QPushButton* reload     = new QPushButton("Reload");
  QPushButton* quit       = new QPushButton("Quit");
  layout->addWidget(start_stop);
  layout->addWidget(reload);
  layout->addWidget(quit);
  layout->setAlignment(Qt::AlignBottom);
  central->setLayout(layout);
  // Window
  setDockOptions(QMainWindow::AnimatedDocks |
                              QMainWindow::AllowNestedDocks |
                              QMainWindow::AllowTabbedDocks);
  addDockWidget(Qt::RightDockWidgetArea, port_status);
  setCentralWidget(central);
  connect(start_stop, &QPushButton::pressed, this, &MainWindow::StartStop);
  connect(reload, &QPushButton::pressed, this, &MainWindow::Reload);
  connect(quit, &QPushButton::pressed, this, &MainWindow::close);
}
void MainWindow::closeEvent(QCloseEvent* event) {
  emit Close();
  QMainWindow::closeEvent(event);
}
} // namespace gui
} // namespace hinan
