// HINAN - simulate H8 microcomputer practice kit
// segment.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_SEGMENT_H_
#define HINAN_SEGMENT_H_

#include "component_interface.h"
#include <QObject>
#include <QLCDNumber>
#include <QVector>
#include <QWidget>

namespace hinan {
namespace components {
class Segment : public ComponentInterface {
 private:
  QVector<QLCDNumber*> segments_;

 public:
  Segment(QWidget*);
  void Update() override;
};
} // namespace components
} // namespace hinan

#endif // HINAN_SEGMENT_H_