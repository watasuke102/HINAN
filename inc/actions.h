// HINAN - simulate H8 microcomputer practice kit
// actions.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_ACTIONS_H_
#define HINAN_ACTIONS_H_

#include <QAction>
#include <QObject>
#include <QToolBar>
#include <QUrl>

namespace hinan {
class Actions : public QObject {
  Q_OBJECT
 private:
  QToolBar* toolbar_;
  QAction*  open_;
  void      Open();

 public:
  Actions();
  QToolBar* Toolbar();

 signals:
  void Opened(QUrl);
};
} // namespace hinan

#endif // HINAN_ACTIONS_H_