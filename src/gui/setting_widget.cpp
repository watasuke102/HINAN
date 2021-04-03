// HINAN - simulate H8 microcomputer practice kit
// mainwindow.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/setting_widget.h"
#include "actions.h"
#include "practice_kit.h"
#include "setting_manager.h"
#include <QApplication>
#include <QColorDialog>
#include <QFormLayout>
#include <QLayout>
#include <QMetaEnum>
#include <QPushButton>
#include <QWidget>

namespace hinan {
namespace gui {
SettingWidget::SettingWidget()
    : update_timeout_(new QSpinBox), check_update_startup_(new QCheckBox),
      show_splash_(new QCheckBox), tact_switch_toggle_(new QCheckBox) {
  QVBoxLayout* main_layout = new QVBoxLayout;

  QFormLayout* form              = new QFormLayout;
  QPushButton* show_color_dialog = new QPushButton(tr("Select"));
  // set default value
  // check update
  show_splash_->setChecked(
      SettingManager::Instance().GetValue(SettingManager::ShowSplashScreen) !=
      QString("false"));
  // splash
  check_update_startup_->setChecked(
      SettingManager::Instance().GetValue(
          SettingManager::CheckUpdateWhenStartup) != QString("false"));
  // timeout
  update_timeout_->setMaximum(60000);
  update_timeout_->setValue(SettingManager::Instance()
                                .GetValue(SettingManager::CheckUpdateTimeOut)
                                .toInt());
  // tact switch
  tact_switch_toggle_->setChecked(
      SettingManager::Instance().GetValue(SettingManager::TactSwitchToggle) !=
      QString("false"));
  // color
  led_color_ =
      QColor(SettingManager::Instance().GetValue(SettingManager::LedColor));
  // add to layout
  form->addRow(tr("Show splash screen on startup"), show_splash_);
  form->addRow(tr("Check update on startup"), check_update_startup_);
  form->addRow(tr("Update timeout (ms)"), update_timeout_);
  form->addRow(tr("Enable toggleable tact switch"), tact_switch_toggle_);
  form->addRow(tr("LED color"), show_color_dialog);
  main_layout->addLayout(form);

  QHBoxLayout* button_box = new QHBoxLayout;
  QPushButton* ok         = new QPushButton(tr("OK"));
  QPushButton* discard    = new QPushButton(tr("Discard"));
  QPushButton* apply      = new QPushButton(tr("Apply"));
  // add to layout
  button_box->addWidget(ok);
  button_box->addWidget(discard);
  button_box->addWidget(apply);
  button_box->setAlignment(Qt::AlignRight);
  main_layout->addLayout(button_box);

  setLayout(main_layout);

  connect(show_color_dialog, &QPushButton::pressed,
          [=] { led_color_ = QColorDialog::getColor(); });
  connect(ok, &QPushButton::pressed, this, &SettingWidget::Ok);
  connect(discard, &QPushButton::pressed, this, &SettingWidget::Discard);
  connect(apply, &QPushButton::pressed, this, &SettingWidget::Apply);
}

void SettingWidget::Ok() {
  Apply();
  SettingManager::Instance().Save();
  close();
}
void SettingWidget::Apply() {
  QMetaEnum list = QMetaEnum::fromType<SettingManager::SettingList>();
  // check update
  SettingManager::Instance().SetValue(
      SettingManager::CheckUpdateWhenStartup,
      QVariant(check_update_startup_->isChecked()).toString());
  // timeout
  SettingManager::Instance().SetValue(
      SettingManager::CheckUpdateTimeOut,
      QString::number(update_timeout_->value()));
  // splash
  SettingManager::Instance().SetValue(
      SettingManager::ShowSplashScreen,
      QVariant(show_splash_->isChecked()).toString());
  // color
  SettingManager::Instance().SetValue(SettingManager::LedColor,
                                      led_color_.name());
  // tact switch
  SettingManager::Instance().SetValue(
      SettingManager::TactSwitchToggle,
      QVariant(tact_switch_toggle_->isChecked()).toString());
}
void SettingWidget::Discard() {
  SettingManager::Instance().Load();
  close();
}
} // namespace gui
} // namespace hinan
