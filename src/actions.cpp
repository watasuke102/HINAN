// HINAN - simulate H8 microcomputer practice kit
// toolbar.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "actions.h"
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QKeySequence>
#include <QObject>
#include <QStyle>
#include <QToolBar>

QIcon Icon(QStyle::StandardPixmap map) {
  return QApplication::style()->standardIcon(map);
}

namespace hinan {
Actions::Actions()
    : toolbar_(new QToolBar()),
      open_(new QAction(Icon(QStyle::SP_DialogOpenButton), tr("Open"))),
      launch_script_(
          new QAction(Icon(QStyle::SP_BrowserReload), tr("Reload script"))),
      reload_script_(
          new QAction(Icon(QStyle::SP_MediaPlay), tr("Launch script"))) {
  // Add shortcut
  open_->setShortcut(QKeySequence::Open);
  launch_script_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  reload_script_->setShortcut(Qt::Key_F5);
  // Add to toolbar
  toolbar_->addActions({open_, reload_script_, launch_script_});
  // connect
  connect(open_, &QAction::triggered, this, &Actions::OpenFileDialog);
  connect(launch_script_, &QAction::triggered, this, &Actions::Launch);
  connect(reload_script_, &QAction::triggered, this, &Actions::Reload);
}
QToolBar* Actions::Toolbar() { return toolbar_; }

void Actions::OpenFileDialog() { emit Opened(QFileDialog::getOpenFileUrl()); }
} // namespace hinan