// HINAN - simulate H8 microcomputer practice kit
// led.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_LED_H_
#define HINAN_LED_H_

#include <QVector>
#include <QObject>
#include <QPushButton>
#include <QWidget>

namespace hinan {
namespace gui {
class LED : public QWidget {
  Q_OBJECT
 private:
  QVector<QPushButton*> leds_;

 public:
  LED(QWidget*);
  void Update();
};
} // namespace gui
} // namespace hinan

#endif // HINAN_LED_H_