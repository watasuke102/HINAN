// HINAN - simulate H8 microcomputer practice kit
// mainwindow.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/setting_widget.h"
#include "core.h"
#include "setting_manager.h"
#include <QApplication>
#include <QColorDialog>
#include <QFormLayout>
#include <QLayout>
#include <QMessageBox>
#include <QMetaEnum>
#include <QPushButton>
#include <QWidget>

namespace hinan {
namespace gui {
SettingWidget::SettingWidget()
    : isChanged_(false), update_timeout_(new QSpinBox),
      check_update_startup_(new QCheckBox), show_splash_(new QCheckBox),
      tact_switch_toggle_(new QCheckBox), color_indicator_(new QPushButton) {
  QVBoxLayout* main_layout = new QVBoxLayout;

  QFormLayout* form              = new QFormLayout;
  QPushButton* show_color_dialog = new QPushButton(tr("Select"));
  // set default value
  InitWidgets();
  // LED color widget
  QHBoxLayout* color = new QHBoxLayout;
  color->addWidget(color_indicator_);
  color->addWidget(show_color_dialog);
  // add to layout
  form->addRow(tr("Show splash screen on startup"), show_splash_);
  form->addRow(tr("Check update on startup"), check_update_startup_);
  form->addRow(tr("Update timeout (ms)"), update_timeout_);
  form->addRow(tr("Enable toggleable tact switch"), tact_switch_toggle_);
  form->addRow(tr("LED color"), color);
  main_layout->addLayout(form);

  QHBoxLayout* button_box  = new QHBoxLayout;
  QPushButton* ok          = new QPushButton(tr("OK"));
  QPushButton* discard     = new QPushButton(tr("Discard"));
  QPushButton* set_default = new QPushButton(tr("Set default settings"));
  // add to layout
  button_box->addWidget(ok);
  button_box->addWidget(discard);
  button_box->addWidget(set_default);
  button_box->setAlignment(Qt::AlignRight);
  main_layout->addLayout(button_box);

  setLayout(main_layout);

  connect(show_color_dialog, &QPushButton::pressed, this,
          &SettingWidget::UpdateColor);
  connect(ok, &QPushButton::pressed, this, &SettingWidget::Ok);
  connect(discard, &QPushButton::pressed, this, &QWidget::close);
  connect(set_default, &QPushButton::pressed, this, &SettingWidget::SetDefault);
}

void SettingWidget::InitWidgets() {
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
  color_indicator_->setDisabled(true);
  color_indicator_->setCheckable(true);
  color_indicator_->setChecked(true);
  led_color_ =
      QColor(SettingManager::Instance().GetValue(SettingManager::LedColor));
  color_indicator_->setStyleSheet(
      QString("QPushButton{ background-color: #222222; }"
              "QPushButton:checked{ background-color: %1; }")
          .arg(led_color_.name()));
}

void SettingWidget::UpdateColor() {
  led_color_ = QColorDialog::getColor();
  color_indicator_->setStyleSheet(
      QString("QPushButton{ background-color: #222222; }"
              "QPushButton:checked{ background-color: %1; }")
          .arg(led_color_.name()));
}

void SettingWidget::Ok() {
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
  SettingManager::Instance().Save();
  Core::InfoDialog(tr("Changes will take effect after restarting software."));
  isChanged_ = false;
  close();
}
void SettingWidget::SetDefault() {
  SettingManager::Instance().SetDefault();
  InitWidgets();
}

void SettingWidget::paintEvent(QPaintEvent* event) {
  isChanged_ = true;
  QWidget::paintEvent(event);
}
void SettingWidget::closeEvent(QCloseEvent* event) {
  if (!isChanged_) {
    QWidget::closeEvent(event);
    return;
  }
  int r =
      Core::YesNoDialog(tr("Changes will be discard.\nDo you want to close?"));
  if (r == QMessageBox::Yes) {
    SettingManager::Instance().Load();
    QWidget::closeEvent(event);
  } else {
    event->ignore();
  }
}

} // namespace gui
} // namespace hinan
