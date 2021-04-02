// HINAN - simulate H8 microcomputer practice kit
// actions.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "actions.h"
#include "core.h"
#include "practice_kit.h"
#include "update_checker.h"
#include <QAction>
#include <QApplication>
#include <QDesktopServices>
#include <QFileDialog>
#include <QKeySequence>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QSize>
#include <QStyle>
#include <QToolBar>

QIcon Icon(QStyle::StandardPixmap map) {
  return QApplication::style()->standardIcon(map);
}

namespace hinan {
Actions::Actions()
    : toolbar_(new QToolBar), menubar_(new QMenuBar),
      file_menu_(new QMenu(tr("File"))), run_menu_(new QMenu(tr("Run"))),
      help_menu_(new QMenu(tr("Help"))), checker_(true) {
  CreateActions();
  // Add shortcut
  open_->setShortcut(QKeySequence::Open);
  startstop_script_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  reload_script_->setShortcut(Qt::Key_F5);
  // Add to toolbar
  toolbar_->addActions({open_, startstop_script_, reload_script_});
  // Create Menubar
  file_menu_->addActions({open_, exit_});
  run_menu_->addActions({startstop_script_, reload_script_});
  help_menu_->addActions({version_, about_qt_, check_update_, view_source_});
  menubar_->addMenu(file_menu_);
  menubar_->addMenu(run_menu_);
  menubar_->addMenu(help_menu_);

  // connect
  connect(open_, &QAction::triggered, [=] {
    QUrl url = QFileDialog::getOpenFileUrl();
    if (!url.isEmpty())
      PracticeKit::Instance().reader->SetPath(url);
  });
  connect(exit_, &QAction::triggered, &QApplication::exit);
  connect(startstop_script_, &QAction::triggered, &PracticeKit::Instance(),
          &PracticeKit::StartStopSignal);
  connect(reload_script_, &QAction::triggered, &PracticeKit::Instance(),
          &PracticeKit::ReloadScript);
  connect(version_, &QAction::triggered, &Core::AboutDialog);
  connect(about_qt_, &QAction::triggered, &QApplication::aboutQt);
  connect(check_update_, &QAction::triggered, [=] { checker_.Check(); });
  connect(view_source_, &QAction::triggered, [] {
    QDesktopServices::openUrl(QUrl("https://github.com/watasuke102/HINAN"));
  });

  // change Start/Stop action's icon
  connect(PracticeKit::Instance().reader, &ProgramReader::ActivatedSignal, this,
          &Actions::ChangeStartStopActionsIcon);
  connect(PracticeKit::Instance().reader, &ProgramReader::DeactivatedSignal,
          this, &Actions::ChangeStartStopActionsIcon);
}
QToolBar* Actions::Toolbar() { return toolbar_; }
QMenuBar* Actions::Menubar() { return menubar_; }

void Actions::CreateActions() {
  open_ = new QAction(QIcon(":/assets/icon/open.svg"), tr("Open"));
  exit_ = new QAction(QIcon(":/assets/icon/exit.svg"), tr("Exit"));
  startstop_script_ =
      new QAction(QIcon(":/assets/icon/start.svg"), tr("Launch script"));
  reload_script_ =
      new QAction(QIcon(":/assets/icon/reload.svg"), tr("Reload script"));
  version_  = new QAction(QIcon(":/assets/icon/info.svg"), tr("Version"));
  about_qt_ = new QAction(QIcon(":/assets/icon/qt.svg"), tr("About Qt"));
  check_update_ =
      new QAction(QIcon(":/assets/icon/update.svg"), tr("Check for update"));
  view_source_ =
      new QAction(QIcon(":/assets/icon/source.svg"), tr("View source code"));
}

void Actions::ChangeStartStopActionsIcon() {
  if (PracticeKit::Instance().reader->IsActive()) {
    startstop_script_->setIcon(QIcon(":/assets/icon/stop.svg"));
    startstop_script_->setText(tr("Terminate script"));
  } else {
    startstop_script_->setIcon(QIcon(":/assets/icon/start.svg"));
    startstop_script_->setText(tr("Launch script"));
  }
}

} // namespace hinan