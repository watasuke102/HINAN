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
      open_(new QAction(Icon(QStyle::SP_DialogOpenButton), "Open")) {
  open_->setShortcut(QKeySequence::Open);
  toolbar_->addAction(open_);
  connect(open_, &QAction::triggered, this, &Actions::Open);
}
QToolBar* Actions::Toolbar() { return toolbar_; }

void Actions::Open() { emit Opened(QFileDialog::getOpenFileUrl()); }
} // namespace hinan