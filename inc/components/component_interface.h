// HINAN - simulate H8 microcomputer practice kit
// component_interface.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_COMPONENT_H_
#define HINAN_COMPONENT_H_

#include <QObject>
#include <QRect>
#include <QWidget>

namespace hinan {
namespace components {
class ComponentInterface : public QWidget {
  Q_OBJECT
 protected:
  QRect original_size_;

 public:
  ComponentInterface(QWidget* parent, int x, int y, int w, int h)
      : QWidget(parent), original_size_(x, y, w, h){};
  virtual void Update() = 0;
  inline QRect OriginalSize() { return original_size_; }
};
} // namespace components
} // namespace hinan

#endif // HINAN_COMPONENT_H_