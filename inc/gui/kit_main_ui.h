// HINAN - simulate H8 microcomputer practice kit
// kit_main_ui.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_KIT_MAIN_UI_H_
#define HINAN_KIT_MAIN_UI_H_

#include <QObject>
#include <QResizeEvent>
#include <QString>
#include <QWidget>
#include <QtSvg/QSvgWidget>

namespace hinan {
namespace gui {
class SvgWidget : public QSvgWidget {
  Q_OBJECT
 public:
  SvgWidget(QWidget*, QString);
  void changeSize(QSize);
};
class KitMainUi : public QWidget {
  Q_OBJECT
 private:
  SvgWidget* widget_;

 public:
  KitMainUi();
  void resizeEvent(QResizeEvent*);
};
} // namespace gui
} // namespace hinan

#endif // HINAN_KIT_MAIN_UI_H_