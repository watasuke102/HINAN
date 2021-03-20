// HINAN - simulate H8 microcomputer practice kit
// tact_switches.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_TACT_SWITCHES_H_
#define HINAN_TACT_SWITCHES_H_

#include "component_interface.h"
#include <QObject>
#include <QPushButton>
#include <QVector>
#include <QWidget>

namespace hinan {
namespace components {
class TactSwitches : public ComponentInterface {
 private:
  QVector<QPushButton*> switches_;

 public:
  TactSwitches(QWidget*);
  void Update() override;
};
} // namespace components
} // namespace hinan

#endif // HINAN_TACT_SWITCHES_H_