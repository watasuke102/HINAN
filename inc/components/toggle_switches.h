// HINAN - simulate H8 microcomputer practice kit
// toggle_switches.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_TOGGLE_SWITCHES_H_
#define HINAN_TOGGLE_SWITCHES_H_

#include "component_interface.h"
#include <QIcon>
#include <QObject>
#include <QPushButton>
#include <QResizeEvent>
#include <QVector>
#include <QWidget>

namespace hinan {
namespace components {
class ToggleSwitches : public ComponentInterface {
 private:
  QVector<QPushButton*> switches_;
  QIcon                 icon_[2];

 public:
  ToggleSwitches(QWidget*);
  void Update() override;
  void resizeEvent(QResizeEvent*);

 public slots:
  void ChangeIcon();
};
} // namespace components
} // namespace hinan

#endif // HINAN_TOGGLE_SWITCHES_H_