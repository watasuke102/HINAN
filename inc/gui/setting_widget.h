// HINAN - simulate H8 microcomputer practice kit
// setting_widget.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_SETTING_WIDGET_H_
#define HINAN_SETTING_WIDGET_H_

#include <QCheckBox>
#include <QCloseEvent>
#include <QColor>
#include <QMouseEvent>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

namespace hinan {
namespace gui {
class SettingWidget : public QWidget {
  Q_OBJECT
 private:
  bool         isChanged_;
  QCheckBox*   show_splash_;
  QCheckBox*   check_update_startup_;
  QSpinBox*    update_timeout_;
  QCheckBox*   tact_switch_toggle_;
  QPushButton* color_indicator_;
  QColor       led_color_;
  void         InitWidgets();

 private slots:
  void UpdateColor();
  void SetDefault();
  void Apply();
  void Ok();
  void Changed();

 public:
  SettingWidget();
  void closeEvent(QCloseEvent*);
};
} // namespace gui
} // namespace hinan

#endif // HINAN_SETTING_WIDGET_H_