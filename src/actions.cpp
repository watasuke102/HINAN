// HINAN - simulate H8 microcomputer practice kit
// toolbar.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "actions.h"
#include "practice_kit.h"
#include <QAction>
#include <QApplication>
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
      startstop_script_(
          new QAction(Icon(QStyle::SP_MediaPlay), tr("Launch script"))),
      reload_script_(
          new QAction(Icon(QStyle::SP_BrowserReload), tr("Reload script"))) {
  // Add shortcut
  open_->setShortcut(QKeySequence::Open);
  startstop_script_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  reload_script_->setShortcut(Qt::Key_F5);
  // Add to toolbar
  toolbar_->addActions({open_, startstop_script_, reload_script_});
  // connect
  connect(open_, &QAction::triggered, [=] {
    PracticeKit::Instance().reader->SetPath(QFileDialog::getOpenFileUrl());
  });
  connect(startstop_script_, &QAction::triggered, &PracticeKit::Instance(),
          &PracticeKit::StartStop);
  connect(reload_script_, &QAction::triggered, &PracticeKit::Instance(),
          &PracticeKit::ReloadScript);
  // change Start/Stop action's icon
  connect(startstop_script_, &QAction::triggered, this,
          &Actions::ChangeStartStopActionsIcon);
}
QToolBar* Actions::Toolbar() { return toolbar_; }

void Actions::ChangeStartStopActionsIcon() {
  if (PracticeKit::Instance().reader->IsActive()) {
    startstop_script_->setIcon(Icon(QStyle::SP_MediaStop));
  } else {
    startstop_script_->setIcon(Icon(QStyle::SP_MediaPlay));
  }
}
} // namespace hinan