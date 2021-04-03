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

#include "update_checker.h"
#include <QAction>
#include <QMenuBar>
#include <QObject>
#include <QToolBar>
#include <QUrl>

namespace hinan {
class Actions : public QObject {
  Q_OBJECT
 private:
  QAction* open_;
  QAction* exit_;
  QAction* startstop_script_;
  QAction* reload_script_;
  QAction* setting_;
  QAction* version_;
  QAction* about_qt_;
  QAction* check_update_;
  QAction* view_source_;

  QMenuBar* menubar_;
  QMenu*    file_menu_;
  QMenu*    run_menu_;
  QMenu*    help_menu_;

  QToolBar*     toolbar_;
  void          CreateActions();
  void          OpenFileDialog();
  void          ChangeStartStopActionsIcon();
  void          ShowSettingWidget();
  UpdateChecker checker_;

 public:
  Actions();
  QToolBar* Toolbar();
  QMenuBar* Menubar();
};
} // namespace hinan

#endif // HINAN_ACTIONS_H_